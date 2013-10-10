/*
 * Velleman K8048 Programmer for FreeBSD and others.
 *
 * Copyright (c) 2005-2013 Darron Broad
 * All rights reserved.
 *
 * Licensed under the terms of the BSD license, see file LICENSE for details.
 */

#include "k8048.h"

#if 0
#define DEBUG
#endif

/*
 * Dot file
 */
void
getdotfile(struct k8048 *k)
{
	char dir[STRLEN], *filename, *homedir, *username;

	filename = getenv("K8048");
	if (filename != NULL && access(filename, R_OK) == 0) {
		snprintf(k->dotfile, STRLEN, "%s", filename);
		return;
	}
	
	if (getcwd(dir, STRLEN) == NULL) {
		printf("%s: fatal error: getcwd failed\n", __func__);
                exit(EX_OSERR); /* Panic */
	}

	snprintf(k->dotfile, STRLEN, "%s/%s", dir, DOTFILENAME);
	if (access(k->dotfile, R_OK) == 0) {
		return;
	}

	homedir = getenv("HOME");
	if (homedir != NULL) {
		snprintf(k->dotfile, STRLEN, "%s/%s", homedir, DOTFILENAME);
		if (access(k->dotfile, R_OK) == 0) {
			return;
		}
	}

	username = getenv("USER");
	if (username != NULL) {
		snprintf(k->dotfile, STRLEN, "/home/%s/%s", username, DOTFILENAME);
		if (access(k->dotfile, R_OK) == 0) {
			return;
		}
	}

	/* No dot file available */
	k->dotfile[0] = '\0';
}

/*
 * Configuration
 */
void
getconf(struct k8048 *k, char *e)
{
	FILE *f1;
	char line[STRLEN];

	/* Configure defaults */
	bzero(k, sizeof(struct k8048));
	k->bitrules = (PGD_IN_PULLUP | PGD_OUT_FLIP | PGC_OUT_FLIP | VPP_OUT_FLIP | PGD_IN_FLIP);
	k->busy = BUSY;
	k->sleep = 1;
	k->fwsleep = 1;
	k->run = 0;

	/* Configure I/O defaults */
	io_config(k);

	/* Load dot file if available */
	getdotfile(k);
#ifdef DEBUG
	printf("%s: DOTFILE=%s\n", __func__, k->dotfile);
#endif
	if (k->dotfile[0] && (f1 = fopen(k->dotfile, "rb")) != NULL) {

		while (fgets(line, STRLEN, f1) != NULL) {
			line[strlen(line) - 1] = '\0'; /* Remove LF */

			if (mystrcasestr(line, "DEVICE=") == line) {
#ifdef DEBUG
				printf("%s: DEVICE=%s\n", __func__, &line[7]);
#endif
				strncpy(k->device, &line[7], STRLEN);
			}
			else if (mystrcasestr(line, "SLEEP=") == line) {
#ifdef DEBUG
				printf("%s: SLEEP=%s\n", __func__, &line[6]);
#endif
				k->sleep = strtoul(&line[6], NULL, 0);
			}
			else if (mystrcasestr(line, "BITRULES=") == line) {
#ifdef DEBUG
				printf("%s: BITRULES=%s\n", __func__, &line[9]);
#endif
				k->bitrules = strtoul(&line[9], NULL, 0);
			}
			else if (mystrcasestr(line, "BUSY=") == line) {
#ifdef DEBUG
				printf("%s: BUSY=%s\n", __func__, &line[5]);
#endif
				k->busy = strtoul(&line[5], NULL, 0);
			}
#ifdef RPI
			else if (mystrcasestr(line, "VPP=") == line) {
#ifdef DEBUG
				printf("%s: VPP=%s\n", __func__, &line[4]);
#endif
				k->gpio.vpp = strtoul(&line[4], NULL, 0);
			}
			else if (mystrcasestr(line, "PGM=") == line) {
#ifdef DEBUG
				printf("%s: PGM=%s\n", __func__, &line[4]);
#endif
				k->gpio.pgm = strtoul(&line[4], NULL, 0);
			}
			else if (mystrcasestr(line, "PGC=") == line) {
#ifdef DEBUG
				printf("%s: PGC=%s\n", __func__, &line[4]);
#endif
				k->gpio.pgc = strtoul(&line[4], NULL, 0);
			}
			else if (mystrcasestr(line, "PGD=") == line) {
#ifdef DEBUG
				printf("%s: PGD=%s\n", __func__, &line[4]);
#endif
				k->gpio.pgdi = strtoul(&line[4], NULL, 0);
				k->gpio.pgdo = k->gpio.pgdi;
			}
			else if (mystrcasestr(line, "PGDO=") == line) {
#ifdef DEBUG
				printf("%s: PGDO=%s\n", __func__, &line[5]);
#endif
				k->gpio.pgdo = strtoul(&line[5], NULL, 0);
			}
			else if (mystrcasestr(line, "PGDI=") == line) {
#ifdef DEBUG
				printf("%s: PGDI=%s\n", __func__, &line[5]);
#endif
				k->gpio.pgdi = strtoul(&line[5], NULL, 0);
			}
#endif
#ifdef MCP23017
			else if (mystrcasestr(line, "MCP=") == line) {
#ifdef DEBUG
				printf("%s: MCP=%s\n", __func__, &line[4]);
#endif
				k->mcp = strtoul(&line[4], NULL, 0);
			}
#endif
			else if (mystrcasestr(line, "RUN=") == line) {
#ifdef DEBUG
				printf("%s: RUN=%s\n", __func__, &line[4]);
#endif
				k->run = strtoul(&line[4], NULL, 0);
			}
			else if (mystrcasestr(line, "FWSLEEP=") == line) {
#ifdef DEBUG
				printf("%s: FWSLEEP=%s\n", __func__, &line[8]);
#endif
				k->fwsleep = strtoul(&line[8], NULL, 0);
			}
			else if (mystrcasestr(line, "DEBUG=") == line) {
#ifdef DEBUG
				printf("%s: DEBUG=%s\n", __func__, &line[6]);
#endif
				k->debug = strtoul(&line[6], NULL, 0);
			}
		}
		fclose(f1);
	} else { /* We are using the defaults */
		snprintf(k->dotfile, STRLEN, "Using defaults (override in %s)", DOTFILENAME);
	}
}