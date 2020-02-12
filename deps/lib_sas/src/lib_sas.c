#include "lib_sas.h"

static sas_err_t __SAS_CalcCrc(const uint16_t * inBuffer, size_t inLen, uint16_t * crc);

static sas_err_t __SAS_CalcCrc(const uint16_t * inBuffer, size_t inLen, uint16_t * crc)
{
	if (inBuffer == NULL) return SAS_ERR_PARAM;

	uint16_t c = 0;
	uint32_t q = 0;
	uint16_t crcval = 0;

	for (; inLen; inLen--)
	{
		c = SAS_To8bit(*inBuffer++);
		q = (crcval ^ c) & 017;
		crcval = (crcval >> 4) ^ (q * 010201);
		q = (crcval ^ (c >> 4)) & 017;
		crcval = (crcval >> 4) ^ (q * 010201);
	}

	*crc = crcval;

	return SAS_ERR_OK;
}

sas_err_t SAS_Init(void)
{
	return SAS_ERR_NOT_IMPLEMENTED;
}

sas_err_t SAS_Deinit(void)
{
	return SAS_ERR_NOT_IMPLEMENTED;
}

sas_err_t SAS_ParsePollRequest(const uint16_t * inBuffer, size_t inLen, uint16_t *outBuffer, size_t * outLen, size_t outMaxLen)
{
	return SAS_ERR_NOT_IMPLEMENTED;
}


sas_err_t SAS_Mock(const uint16_t * inBuffer, size_t inLen, uint16_t *outBuffer, size_t * outLen, size_t outMaxLen)
{
	if (inBuffer == NULL) return SAS_ERR_PARAM;
	if (inLen == 0) return SAS_ERR_PARAM;
	if (outBuffer == NULL) return SAS_ERR_PARAM;
	if (outLen == NULL) return SAS_ERR_PARAM;
	if (outMaxLen == 0) return SAS_ERR_PARAM;

	sas_err_t err = SAS_ERR_OK;
	static uint8_t generalCode = 0;

	if (inLen == 1)
	{
		if (SAS_IsWakeup(inBuffer[0]) && SAS_IsWakeup(inBuffer[0]))
		{
			sas_general_code_t code = 0x10 + (generalCode % 10);
			*outLen = 1;
			*outBuffer = SAS_To9bit(code);
			return SAS_ERR_OK;
		}
		else
		{
			return SAS_ERR_DATA;
		}
	}

	if (inLen >= 4)
	{
		// As minimum we have address, command and two CRC bytes

		// Check CRC

		// Parse command and form answer
		switch (SAS_To8bit(inBuffer[2]))
		{
		case SAS_LP_SHUTDOWN:
			break;

		case SAS_LP_STARTUP:
			break;

		case SAS_LP_SOUND_OFF:
			break;

		case SAS_LP_SOUND_ON:
			break;

		case SAS_LP_SEND_GAMES_WON_METER:
			break;

		case SAS_LP_SEND_GAMES_LOST_METER:
			break;

		case SAS_LP_SEND_CARD_INFO:
			break;

		default:
			// TODO send NACK
			break;
		}

		// In case unknown command - just return nak
	}

	return err;
}
