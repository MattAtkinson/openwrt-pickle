/*
 * Copyright (C) 2005-2014 Darron Broad
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name `Darron Broad' nor the names of any contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "k8048.h"

/*
 * DETERMINE ARCH
 *
 *  k12 | k14 | k16 | k24 | k32
 */
uint32_t
pic_arch(struct k8048 *k, const char *execname)
{
#ifdef K12
	if (strcmp(execname, "k12") == 0)
		return pic12_arch(k);	/* 12-bit word PIC10F/PIC12F/PICF */
#endif
#ifdef K14
	if (strcmp(execname, "k14") == 0)
		return pic14_arch(k);	/* 14-bit word PIC10F/PIC12F/PICF */
#endif
#ifdef K16
	if (strcmp(execname, "k16") == 0)
		return pic16_arch(k);	/* 16-bit word PIC18F */
#endif
#ifdef K24
	if (strcmp(execname, "k24") == 0)
		return pic24_arch(k);	/* 24-bit word PIC24/dsPIC */
#endif
#ifdef K32
	if (strcmp(execname, "k32") == 0)
		return pic32_arch(k);	/* 32-bit word PIC32 */
#endif
	return 0;
}

/*
 * COMPARE DEVICE NAMES FOR QSORT
 */
int
pic_cmp(const void *p1, const void *p2)
{
	char *s1 = *(char **)p1, *s2 = *(char **)p2;

	return strcasecmp(s1, s2);
}

/*
 * DUMP DEVICE SELECTION
 */
void
pic_selector(struct k8048 *k)
{
	if (k->pic->selector)
		k->pic->selector();
	else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * LOOK UP PE FILE
 */
int
pic_pe_lookup(struct k8048 *k, char *pathname, const char *filename)
{
	if (k->etc[0]) {
		snprintf(pathname, STRLEN, "%s/%s", k->etc, filename);
		if (access(pathname, R_OK) == 0)
			return 0;
	}

	char *dotdup = (char *)strdup(k->dotfile);
	if (dotdup == NULL) {
		printf("%s: fatal error: strdup failed\n", __func__);
		io_exit(k, EX_OSERR); /* Panic */
	}

	char *dname = dirname(dotdup);
	snprintf(pathname, STRLEN, "%s/%s", dname, filename);
	free(dotdup);
	if (access(pathname, R_OK) == 0)
		return 0;

	bzero(pathname, STRLEN);
	return -1;
}

/*
 * READ CONFIG
 */
void
pic_read_config(struct k8048 *k, int flag)
{
	if (k->pic->read_config_memory)
		k->pic->read_config_memory(k, flag);
	else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * DETERMINE PROGRAM FLASH SIZE
 *
 *  INVOKE AFTER `pic_read_config'
 */
uint32_t
pic_get_program_size(struct k8048 *k, uint32_t *addr)
{
	uint32_t size = UINT32_MAX;

	if (k->pic->get_program_size)
		size = k->pic->get_program_size(addr);
	else
		printf("%s: information: unimplemented\n", __func__);

	return size;
}

/*
 * DETERMINE DATA EEPROM/FLASH SIZE
 *
 *  INVOKE AFTER `pic_read_config'
 */
uint32_t
pic_get_data_size(struct k8048 *k, uint32_t *addr)
{
	uint32_t size = UINT32_MAX;

	if (k->pic->get_data_size)
		size = k->pic->get_data_size(addr);
	else
		printf("%s: information: unimplemented\n", __func__);

	return size;
}

/*
 * DETERMINE EXECUTIVE SIZE
 *
 *  INVOKE AFTER `pic_read_config'
 */
uint32_t
pic_get_executive_size(struct k8048 *k, uint32_t *addr)
{
	uint32_t size = UINT32_MAX;

	if (k->pic->get_executive_size)
		size = k->pic->get_executive_size(addr);
	else
		printf("%s: information: unimplemented\n", __func__);

	return size;
}

/*
 * DETERMINE BOOT FLASH SIZE
 *
 *  INVOKE AFTER `pic_read_config'
 */
uint32_t
pic_get_boot_size(struct k8048 *k, uint32_t *addr)
{
	uint32_t size = UINT32_MAX;

	if (k->pic->get_boot_size)
		size = k->pic->get_boot_size(addr);
	else
		printf("%s: information: unimplemented\n", __func__);

	return size;
}

/*
 * READ PROGRAM FLASH / DATA FLASH MEMORY BLOCK
 *
 *  INVOKE AFTER `pic_get_program_size'
 */
uint32_t
pic_read_program_memory_block(struct k8048 *k, uint32_t *data, uint32_t addr, uint32_t size)
{
	uint32_t rc = UINT32_MAX;

	if (k->pic->read_program_memory_block)
		rc = k->pic->read_program_memory_block(k, data, addr, size);
	else
		printf("%s: information: unimplemented\n", __func__);

	return rc;
}

/*
 * READ DATA EEPROM/FLASH MEMORY BLOCK 
 *
 *  INVOKE AFTER `pic_get_data_size'
 */
uint32_t
pic_read_data_memory_block(struct k8048 *k, uint16_t *data, uint32_t addr, uint16_t size)
{
	uint32_t rc = UINT32_MAX;

	if (k->pic->read_data_memory_block)
		rc = k->pic->read_data_memory_block(k, data, addr, size);
	else
		printf("%s: information: unimplemented\n", __func__);

	return rc;
}
 
/*
 * PROGRAM
 */
void
pic_program(struct k8048 *k, char *filename, int blank)
{
	if (k->pic->program) {
		pic_read_config(k, PIC_CONFIG_ONLY);

		k->pic->program(k, filename, blank);
	} else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * VERIFY DEVICE
 *
 *  RETURN NUMBER OF VERIFY ERRORS
 */
uint32_t
pic_verify(struct k8048 *k, char *filename)
{
	uint32_t fail = UINT32_MAX;
	
	if (k->pic->verify) {
		pic_read_config(k, PIC_CONFIG_ONLY);

		fail = k->pic->verify(k, filename);
	} else
		printf("%s: information: unimplemented\n", __func__);

	return fail;
}

/*
 * DRY RUN
 */
void
pic_dryrun(struct k8048 *k, char *filename)
{
	if (k->pic->dryrun)
		k->pic->dryrun(k, filename);
	else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * WRITE BANDGAP CONFIG
 */
void
pic_writebandgap(struct k8048 *k, uint16_t bandgap)
{
	if (k->pic->arch == ARCH14BIT) {
		pic_read_config(k, PIC_CONFIG_ONLY);

		if (k->pic->bulk_erase)
			k->pic->bulk_erase(k, PIC_INTERNAL, bandgap);
		else
			printf("%s: information: unimplemented\n", __func__);
	} else
		printf("%s: information: BANDGAP is not supported on this architecture\n", __func__);
}

/*
 * WRITE OSCILLATOR CALIBRATION
 */
void
pic_writeosccal(struct k8048 *k, uint16_t osccal)
{
	if (k->pic->arch == ARCH12BIT || k->pic->arch == ARCH14BIT) {
		pic_read_config(k, PIC_CONFIG_ONLY);

		if (k->pic->bulk_erase)
			k->pic->bulk_erase(k, osccal, PIC_INTERNAL);
		else
			printf("%s: information: unimplemented\n", __func__);
	} else
		printf("%s: information: OSCCAL is not supported on this architecture\n", __func__);
}

/*
 * BLANK A DEVICE
 *
 * DISABLE PROTECTION AND BULK ERASE
 */
void
pic_blank(struct k8048 *k)
{
	if (k->pic->bulk_erase) {
		pic_read_config(k, PIC_CONFIG_ONLY);

		k->pic->bulk_erase(k, PIC_INTERNAL, PIC_INTERNAL);
	} else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * ERASE ROW(S)
 */
void
pic_erase(struct k8048 *k, uint32_t row, uint32_t nrows)
{
	if (k->pic->row_erase) {
		pic_read_config(k, PIC_CONFIG_ONLY);

		k->pic->row_erase(k, row, nrows);
	} else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * DUMP DEVICE ID
 */
void
pic_dumpdeviceid(struct k8048 *k)
{
	if (k->pic->dumpdeviceid) {
		pic_read_config(k, PIC_CONFIG_ALL);

		k->pic->dumpdeviceid(k);
	} else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * DUMP CONFIGURATION
 */
void
pic_dumpconfig(struct k8048 *k)
{
	if (k->pic->dumpconfig) {
		pic_read_config(k, PIC_CONFIG_ONLY);

		k->pic->dumpconfig(k, PIC_VERBOSE);
	} else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * DUMP OSCILLATOR CALIBRATION
 */
void
pic_dumposccal(struct k8048 *k)
{
	if (k->pic->arch == ARCH12BIT || k->pic->arch == ARCH14BIT) {
		pic_read_config(k, PIC_CONFIG_ALL);

		if (k->pic->dumposccal)
			k->pic->dumposccal(k);
		else
			printf("%s: information: unimplemented\n", __func__);
	} else
		printf("%s: information: OSCCAL is not supported on this architecture\n", __func__);
}

/******************************************************************************
  INHX32 DATA DUMP
 *****************************************************************************/

/*
 * DUMP EXTENDED ADDRESS
 *
 * :BBAAAATTHHHHCC
 *  
 *  BB   02   = NUMBER OF BYTES
 *  AAAA 0000 = ADDRESS (0000)
 *  TT   04   = EXTENDED_LINEAR_ADDRESS
 *  HHHH      = EXTENDED ADDRESS << 16
 *  CC        = CHECKSUM
 *
 *  FLAG=1 UPDATE AND OUTPUT ALWAYS
 *  FLAG=0 UPDATE AND OUTPUT IF CHANGED
 */
void
pic_dumpaddr(uint32_t addr, int flag)
{
	static uint16_t oldaddr = 0;
	uint16_t newaddr = addr >> 16;

	if (flag || (newaddr != oldaddr)) {
		uint8_t hb = newaddr >> 8;
		uint8_t lb = newaddr & 0xFF;
		uint8_t cc = 0x100 - 0x06 - hb - lb;
		printf(":02000004%02X%02X%02X\n", hb, lb, cc);
	}
	oldaddr = newaddr;
}

/*
 * DUMP 8-BIT BYTE AS INHX32 DATA
 */
void
pic_dumpbyte(uint32_t addr, uint8_t byte)
{
	uint8_t cc, hb, lb;
	hb = addr >> 8;
	lb = addr;
	printf(":01%02X%02X00", hb, lb);
	cc = 0x01 + hb + lb + 0x00;
	lb = byte;
	cc = cc + lb;
	printf("%02X%02X\n", lb, (0x100 - cc) & 0xFF);
}

/*
 * DUMP 16-BIT WORD AS INHX32 DATA
 */
void
pic_dumpword16(uint32_t addr, uint16_t word)
{
	uint8_t cc, hb, lb;
	hb = addr >> 7;
	lb = addr << 1;
	printf(":02%02X%02X00", hb, lb);
	cc = 0x02 + hb + lb + 0x00;
	hb = word >> 8;
	lb = word;
	cc = cc + hb + lb;
	printf("%02X%02X%02X\n", lb, hb, (0x100 - cc) & 0xFF);
}

/*
 * DUMP 32-BIT WORD AS INHX32 DATA
 */
void
pic_dumpword32(uint32_t addr, uint32_t word)
{
	uint8_t cc, b3, b2, b1, b0;
	b1 = addr >> 7;
	b0 = addr << 1;
	printf(":04%02X%02X00", b1, b0);
	cc = 0x04 + b1 + b0 + 0x00;
	b3 = word >> 24;
	b2 = word >> 16;
	b1 = word >> 8;
	b0 = word;
	cc = cc + b3 + b2 + b1 + b0;
	printf("%02X%02X%02X%02X%02X\n", b0, b1, b2, b3, (0x0100 - cc) & 0xFF);
}

/*
 * DUMP DEVICE AS INHX32 DATA
 */
void
pic_dumpdevice(struct k8048 *k)
{
	uint32_t addr, size;

	/* Get userid/config */
	pic_read_config(k, PIC_CONFIG_ALL);

	/* Program flash */
	if (k->pic->get_program_size) {
		/* Get program flash size */
		size = pic_get_program_size(k, &addr);
		if (size == UINT32_MAX) {
			printf("%s: fatal error: program flash size invalid\n", __func__);
			io_exit(k, EX_SOFTWARE); /* Panic */
		}
		/* Dump program flash */
		if (size)
			pic_dump_program(k, addr, size, PIC_INHX32);
	}

	/* Boot flash */
	if (k->pic->get_boot_size) {
		/* Get boot flash size */
		size = pic_get_boot_size(k, &addr);
		if (size == UINT32_MAX) {
			printf("%s: fatal error: program flash size invalid\n", __func__);
			io_exit(k, EX_SOFTWARE); /* Panic */
		}
		/* Dump boot flash */
		if (size)
			pic_dump_program(k, addr, size, PIC_INHX32);
	}

	/* Data EEPROM/flash */
	if (k->pic->get_data_size) {
		/* Get data EEPROM/flash size */
		size = pic_get_data_size(k, &addr);
		if (size == UINT32_MAX) {
			printf("%s: fatal error: data EEPROM/flash size invalid\n", __func__);
			io_exit(k, EX_SOFTWARE); /* Panic */
		}
		/* Dump data EEPROM/flash */
		if (size)
			pic_dump_data(k, addr, size, PIC_INHX32);
	}

	/* Userid/Config */
	if (k->pic->dumpdevice) {
		k->pic->dumpdevice(k);
	}

	/* EOF */
	printf(":00000001FF\n");
}

/******************************************************************************
  HEXADECIMAL DATA DUMP
 *****************************************************************************/

/*
 * DUMP ADDRESS/SIZE ADJUST
 */
int
pic_dumpadj(struct k8048 *k, uint32_t *baddr, uint32_t *bsize, uint32_t naddr, uint32_t nwords)
{
	if (naddr != UINT32_MAX) {
		uint32_t laddr = *baddr + (*bsize * k->pic->dumpadj);
		if (naddr >= *baddr && naddr < laddr) {
			*bsize -= (naddr - *baddr) / k->pic->dumpadj;
			*baddr = naddr;
		} else if (naddr != *baddr) {
			printf("%s: information: address invalid\n", __func__);
			return -1;
		}
	}
	if (nwords != UINT32_MAX) {
		if (nwords < *bsize)
			*bsize = nwords;
	}
	return 0;
}

/*
 * DUMP PROGRAM FLASH IN HEX
 */
void
pic_dumpprogram(struct k8048 *k, uint32_t a, uint32_t n)
{
	uint32_t addr, size;

	if (!k->pic->get_program_size) {
		printf("%s: information: program flash is not supported on this architecture\n", __func__);
		return;
	}

	pic_read_config(k, PIC_CONFIG_ONLY);

	/* Get program flash size */
	size = pic_get_program_size(k, &addr);
	if (size == UINT32_MAX) {
		printf("%s: fatal error: program flash size invalid\n", __func__);
		io_exit(k, EX_SOFTWARE); /* Panic */
	}
	if (size == 0) {
		printf("%s: information: program flash is not supported on this device\n", __func__);
		return;
	}
	/* Adjust address and size */
	if (pic_dumpadj(k, &addr, &size, a, n))
		return;
	/* Dump program flash */
	pic_dump_program(k, addr, size, PIC_HEXDEC);
}

/*
 * DUMP DATA EEPROM/FLASH IN HEX
 */
void
pic_dumpdata(struct k8048 *k)
{
	uint32_t addr, size;

	if (!k->pic->get_data_size) {
		printf("%s: information: data EEPROM/flash is not supported on this architecture\n", __func__);
		return;
	}

	pic_read_config(k, PIC_CONFIG_ONLY);

	/* Get data EEPROM/data flash size */
	size = pic_get_data_size(k, &addr);
	if (size == UINT32_MAX) {
		printf("%s: fatal error: data EEPROM/flash size invalid\n", __func__);
		io_exit(k, EX_SOFTWARE); /* Panic */
	}
	if (size == 0) {
		printf("%s: information: data EEPROM/flash is not supported on this device\n", __func__);
		return;
	}
	/* Dump data EEPROM/flash */
	pic_dump_data(k, addr, size, PIC_HEXDEC);
}

/*
 * DUMP EXECUTIVE FLASH IN HEX
 */
void
pic_dumpexec(struct k8048 *k, uint32_t a, uint32_t n)
{
	uint32_t addr, size;

	if (!k->pic->get_executive_size) {
		printf("%s: information: EXECUTIVE flash is not supported on this architecture\n", __func__);
		return;
	}

	pic_read_config(k, PIC_CONFIG_ONLY);

	/* Get program executive size */
	size = pic_get_executive_size(k, &addr);
	if (size == UINT32_MAX) {
		printf("%s: fatal error: EXECUTIVE flash size invalid\n", __func__);
		io_exit(k, EX_SOFTWARE); /* Panic */
	}
	if (size == 0) {
		printf("%s: information: EXECUTIVE flash is not supported on this device\n", __func__);
		return;
	}
	/* Adjust address and size */
	if (pic_dumpadj(k, &addr, &size, a, n))
		return;
	/* Dump program executive */
	pic_dump_program(k, addr, size, PIC_HEXDEC);
}

/*
 * DUMP BOOT FLASH IN HEX
 */
void
pic_dumpboot(struct k8048 *k, uint32_t a, uint32_t n)
{
	uint32_t addr, size;

	if (!k->pic->get_boot_size) {
		printf("%s: information: BOOT flash is not supported on this architecture\n", __func__);
		return;
	}

	pic_read_config(k, PIC_CONFIG_ONLY);

	/* Get boot flash size */
	size = pic_get_boot_size(k, &addr);
	if (size == UINT32_MAX) {
		printf("%s: fatal error: BOOT flash size invalid\n", __func__);
		io_exit(k, EX_SOFTWARE); /* Panic */
	}
	if (size == 0) {
		printf("%s: information: BOOT flash is not supported on this device\n", __func__);
		return;
	}
	/* Adjust address and size */
	if (pic_dumpadj(k, &addr, &size, a, n))
		return;
	/* Dump boot flash */
	pic_dump_program(k, addr, size, PIC_HEXDEC);
}

/******************************************************************************
  DUMP HEX / INHX32 PROGRAM AND DATA
 *****************************************************************************/

/*
 * DUMP PROGRAM FLASH
 */
void
pic_dump_program(struct k8048 *k, uint32_t addr, uint32_t size, int mode)
{
	/* Allocate program array */
	uint32_t *data = (uint32_t *)calloc(size + 16, sizeof(uint32_t));
	if (data == NULL) {
		printf("%s: fatal error: calloc failed\n", __func__);
		io_exit(k, EX_OSERR); /* Panic */
	}
	/* Read program */
	if (pic_read_program_memory_block(k, data, addr, size) == UINT32_MAX) {
		printf("%s: fatal error: program flash read failed\n", __func__);
		io_exit(k, EX_SOFTWARE); /* Panic */
	}
	/* Dump */
	if (mode == PIC_HEXDEC) {
		pic_dumphexcode(k, addr, size, data);
	} else if (mode == PIC_INHX32) {
		pic_dumpinhxcode(k, addr, size, data);
	}
	free(data);
}

/*
 * DETECT EMPTY PROGRAM FLASH ROW
 */
int
pic_mtcode(uint32_t compar, uint32_t size, uint32_t *data)
{
	uint32_t mtrow = 0;

	for (uint32_t j = 0; j < size; ++j) {
		if (data[j] == compar)
			mtrow++;
	}
	return (mtrow == size);
}

/*
 * DUMP HEX PROGRAM FLASH WORDS
 */
void
pic_dumphexcode(struct k8048 *k, uint32_t addr, uint32_t size, uint32_t *data)
{
	if (k->pic->dumphexcode)
		k->pic->dumphexcode(k, addr, size, data);
	else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * DUMP INHX32 PROGRAM FLASH WORDS
 */
void
pic_dumpinhxcode(struct k8048 *k, uint32_t addr, uint32_t size, uint32_t *data)
{
	if (k->pic->dumpinhxcode)
		k->pic->dumpinhxcode(k, addr, size, data);
	else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * DUMP DATA EEPROM/FLASH
 */
void
pic_dump_data(struct k8048 *k, uint32_t addr, uint32_t size, int mode)
{
	/* Allocate data EEPROM/flash array */
	uint16_t *data = (uint16_t *)calloc(size + 16, sizeof(uint16_t));
	if (data == NULL) {
		printf("%s: fatal error: calloc failed\n", __func__);
		io_exit(k, EX_OSERR); /* Panic */
	}
	/* Read data EEPROM/flash */
	if (pic_read_data_memory_block(k, data, addr, size) == UINT32_MAX) {
		printf("%s: fatal error: data EEPROM/flash read failed\n", __func__);
		io_exit(k, EX_SOFTWARE); /* Panic */
	}
	/* Dump */
	if (mode == PIC_HEXDEC) {
		pic_dumphexdata(k, addr, size, data);
	} else if (mode == PIC_INHX32) {
		pic_dumpinhxdata(k, addr, size, data);
	}
	free(data);
}

/*
 * DETECT EMPTY DATA EEPROM/FLASH ROW
 */
int
pic_mtdata(uint16_t compar, uint32_t size, uint16_t *data)
{
	uint32_t mtrow = 0;

	for (uint32_t j = 0; j < size; ++j) {
		if (data[j] == compar)
			mtrow++;
	}
	return (mtrow == size);
}

/*
 * DUMP HEX DATA EEPROM/FLASH BYTES/WORDS
 */
void
pic_dumphexdata(struct k8048 *k, uint32_t addr, uint32_t size, uint16_t *data)
{
	if (k->pic->dumphexdata)
		k->pic->dumphexdata(k, addr, size, data);
	else
		printf("%s: information: unimplemented\n", __func__);
}

/*
 * DUMP INHX32 DATA EEPROM/FLASH BYTES/WORDS
 */
void
pic_dumpinhxdata(struct k8048 *k, uint32_t addr, uint32_t size, uint16_t *data)
{
	if (k->pic->dumpinhxdata)
		k->pic->dumpinhxdata(k, addr, size, data);
	else
		printf("%s: information: unimplemented\n", __func__);
}

/******************************************************************************
  PANEL WRITING
 *****************************************************************************/

/*
 * WRITE PANEL
 *
 *  mode:
 *  	PIC_PANEL_BEGIN
 *  		data1: 	memory region
 *  		data2:	memory size
 *
 *  	PIC_PANEL_UPDATE
 *  		data1:	memory address
 *  		data2:	memory data
 *
 *  	PIC_PANEL_END
 *  		data1:	void
 *  		data2:	void
 */
void
pic_write_panel(struct k8048 *k, int mode, uint32_t data1, uint32_t data2)
{
	static uint32_t write_pending = 0;
	static uint32_t panel_region = PIC_REGIONNOTSUP;
	static uint32_t panel_address = 0;
	static uint32_t *panel = NULL;
	static uint32_t panel_size = 0;

	if (k->pic->write_panel == NULL) {
		printf("%s: fatal error: write panel unimplemented\n", __func__);
		io_exit(k, EX_SOFTWARE); /* Panic */
	}
	if (mode == PIC_PANEL_BEGIN || mode == PIC_PANEL_END) {
		if (panel) {
			if (write_pending) {
				write_pending = 0;
				k->pic->write_panel(k, panel_region, panel_address, panel, panel_size);
			}
			free(panel);
			panel_region = PIC_REGIONNOTSUP;
			panel_address = 0;
			panel = NULL;
			panel_size = 0;
		}
	}
	if (mode == PIC_PANEL_BEGIN) {
		panel_region = data1;		/* MEMORY REGION */
		panel_size = data2;		/* MEMORY SIZE   */
	}
	if (mode == PIC_PANEL_BEGIN || mode == PIC_PANEL_UPDATE) {
		if (panel == NULL) {
			if (panel_size == 0) {
				printf("%s: fatal error: zero sized panel\n", __func__);
				io_exit(k, EX_SOFTWARE); /* Panic */
			}
			panel = malloc(sizeof(uint32_t) * panel_size);
			if (panel == NULL) {
				printf("%s: fatal error: malloc failed\n", __func__);
				io_exit(k, EX_SOFTWARE); /* Panic */
			}
			memset((void *)panel, -1, sizeof(uint32_t) * panel_size);
		}
	}
	if (mode == PIC_PANEL_UPDATE) {
		uint32_t address, new_address, boundary, mask;

		boundary = 0 - panel_size;
		mask = panel_size - 1;
		address = data1;		/* MEMORY ADDRESS */
		new_address = address & boundary;
		if (new_address != panel_address) {
			if (write_pending) {
				write_pending = 0;
				k->pic->write_panel(k, panel_region, panel_address, panel, panel_size);
				memset((void *)panel, -1, sizeof(uint32_t) * panel_size);
			}
			panel_address = new_address;
		}
		panel[address & mask] = data2;	/* MEMORY DATA */
		write_pending++;
	}
}
