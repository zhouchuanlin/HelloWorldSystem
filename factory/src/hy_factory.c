#include"hy_factory.h"
#iinini
FACTORY_IN_T *FACTORY_IN = NULL;

static char* trim(char *str)
{
	char *p = str + strlen(str) - 1;
	while (' ' == *p || '\t' == *p || '\n' == *p || '\r' == *p)
	{
		*p = '\0';
		p--;
	}
	return str;
}

static void mdelay_wait(u16 ms)
{
	u16 i = 0;
	for (i = 0; i < ms; i++)
	{
		sl_udelay_wait(1000); //1ms
	}
}

bool Factory_WaitingToEnter()
{
	FACTORY_IN = (FACTORY_IN_T*) malloc(sizeof(FACTORY_IN_T));
	printf("Factory: waiting to enter factory mode\r\n");

	u8 factory_test_wait_time = 5; // default 5s
	while (factory_test_wait_time > 0)
	{
		mdelay_wait(1000);
		if (strstr((const char*) FACTORY_IN->buf, FACTORY_MODE_FLAG))
		{
			memset(FACTORY_IN->buf, 0, sizeof(FACTORY_IN->buf));
			FACTORY_IN->len = 0;
			printf("\r\n------ Factory Mode ------\r\nOK\r\n\r\n");
			return 1;
		}
		factory_test_wait_time--;
	}
	free(FACTORY_IN);
	return 0;
}

static void s_printf(char *str)
{
	u16 i = 0;
	u16 size = strlen(str);
	for (i = 0; i < size; i++)
	{
		printf("%c", str[i]);
	}
}

void Factory_Process()
{
	char req[FACTORY_REQ_SIZE] =
	{ 0 };
	char rsp[FACTORY_RSP_SIZE] =
	{ 0 };
	u8 size = sizeof(FACTORY_CMDS) / sizeof(FACTORY_CMDS[0]);

	while (1)
	{
		u8 i = 0;

		for (i = 0; i < size; i++)
		{
			char *p = strstr((const char*) FACTORY_IN->buf,
					FACTORY_CMDS[i].cmd);
			if (p != NULL)
			{
				memset(req, 0, sizeof(req));
				memset(rsp, 0, sizeof(rsp));

				mdelay_wait(100);
				sprintf(req, "%s", p);
				trim(req);

				s_printf(req);
				printf("\r\n");

				if (FACTORY_CMDS[i].cmd_handle(req, rsp) == CMD_OK)
				{
					if (strlen(rsp) > 0)
					{
						s_printf(rsp);
						printf("\r\n");
					}
					printf("+OK\r\n\r\n");
				}
				else
				{
					if (strlen(rsp) > 0)
					{
						s_printf(rsp);
						printf("\r\n");
					}
					printf("+ERROR\r\n\r\n");
				}

				memset(FACTORY_IN->buf, 0, sizeof(FACTORY_IN->buf));
				FACTORY_IN->len = 0;
				break;
			}
		}
	}
}

void Factory_OnUartEvent(u8 byte)
{
	if (FACTORY_IN != NULL)
	{
		if (FACTORY_IN->len >= FACTORY_BUF_SIZE)
		{
			FACTORY_IN->len = 0;
		}
		FACTORY_IN->buf[FACTORY_IN->len++] = byte;
	}
}
