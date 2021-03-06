/* ------------------------------------
 * Program to show what keycodes evnt_multi & co.
 * return...
 */

#ifdef __AHCC__
# include <aes.h>
# include <tos.h>
#else
# ifdef __SOZOBONX__
#  include <minimum.h>
#  include <osbind.h>
#  include <xgemfast.h>
# endif
#endif
#include <stdlib.h>
#include <stdio.h>

#ifndef FALSE
#define FALSE 0
#define TRUE  !FALSE
#endif

/* resource set indices for KEYTEST */
#define TREEMENU   0 /* menu */
#define MENUINFO   7 /* STRING in tree TREE001 */
#define MENUTABL  16 /* STRING in tree TREE001 */
#define MENUQUIT  18 /* STRING in tree TREE001 */

#define MY_MU (MU_MESAG | MU_KEYBD)

OBJECT *tree_menu;

/* ------------------------------------
 * Function prototypes.
 */
static void prg_init (void);
static void prg_exit (void);
static void msg_handler (short *msgbuf);
static void do_menu (short entry);
static void ascii_table (void);
static void show_key (short key, short state);

/* ------------------------------------
 * Standard GEM handling functions (main loop).
 */

int main()
{
	short  mbuf[8];
	short  evnt_m, m1fl, pmx1, pmy1, pm1w, pm1h,
	       m2fl, pmx2, pmy2, pm2w, pm2h, pmx, pmy, pmstate,
	       state, key, clicks, tlo_cnt, thi_cnt;
	m1fl = pmx1 = pmy1 = pm1w = pm1h = 0;
	m2fl = pmx2 = pmy2 = pm2w = pm2h = 0;
	tlo_cnt = thi_cnt = 0;

	prg_init ();
	graf_mouse(0, ARROW);
	while (TRUE) {
		/* mouse button, mouse coordinate 1,
		 * mouse coordinate 2, message and timer events.
		 * mouse coordinate, mouse button, special key and normal key states.
		 * number of mouse clicks.
		 */
		evnt_m = evnt_multi(MY_MU, 259, 3, 0, m1fl, pmx1, pmy1, pm1w, pm1h,
				    m2fl, pmx2, pmy2, pm2w, pm2h, mbuf, tlo_cnt, thi_cnt,
				    &pmx, &pmy, &pmstate ,&state, &key, &clicks);

		if (evnt_m & MU_MESAG)
			msg_handler (mbuf);

		if (evnt_m & MU_KEYBD)
			show_key (key, state);
	}
	return 0;
}

/* ------------------------------------
 * GEM startup.
 */
static void prg_init (void)
{
	appl_init ();

	if (!rsrc_load ("keytest.rsc")) {
		appl_exit ();
		exit (1);
	}

	/* TREEMENU should be defines, generated by the rsc editor */
	rsrc_gaddr (R_TREE, TREEMENU, &tree_menu);
	menu_bar (tree_menu, TRUE);		/* show menubar */
}

/* GEM exit. */
static void prg_exit (void)
{
	menu_bar (tree_menu, FALSE);
	rsrc_free ();
	appl_exit ();
	exit (0);
}

/* message handling code. */
static void msg_handler (short *msgbuf)
{
	switch (msgbuf[0]) {
	case MN_SELECTED:
		/* handle menu entry */
		do_menu (msgbuf[4]);
		/* de-invert menu title */
		menu_tnormal (tree_menu, msgbuf[3], 1);
		break;
	}
}

/* ------------------------------------
 * Selection handling functions.
 */
static void do_menu (short entry)
{
	switch (entry) {
	case MENUINFO:
		form_alert (1, "[1][|Show keycodes and status|  of shift/alt/ctrl as|returned by evnt_multi()][ OK ]");
		break;

	case MENUTABL:
		ascii_table ();
		break;
		
	case MENUQUIT:
		prg_exit ();
	}
}

static void ascii_table (void)
{
	int x, y;
	Cconws ("\33Y#  . | 0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f \15\12");
	Cconws ("----------------------------------------------------\15\12");

	for (y = 2; y < 16; y ++) {
		Cconout(' ');
		Cconout('0' + y);
		Cconout(' ');
		Cconout('|');
		
		for (x = 0; x < 16; x ++) {
			Cconout(' ');
			Cconout(x + y * 0x10);
			Cconout(' ');
		}
		Cconws("\15\12");
	}
}

void show_key (short key, short state)
{
	char  buf[128];

	sprintf (buf, "[1][Mod state:  $%02x (%d)|Scan code:  $%02x (%d)|ASCII code: $%02x (%d)][ OK ]",
		 state, state, key>>8, key>>8, key&0xff, key&0xff);
	form_alert (1, buf);

	if ((key & 0xFF) == 27)
		prg_exit ();
}
