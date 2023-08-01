#include <glib.h>
#include <gtk/gtk.h>
#include <pango/pango.h>
#include <pango/pangocairo.h>

#include <fontconfig/fontconfig.h>

#include <arpa/inet.h>
#include <errno.h>
#include <ifaddrs.h>
#include <locale.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define VERSION_PROGRAM "4.0.2"

extern GtkWidget *entryIpAddress;
extern GtkWidget *entryMaskPrefix;

extern GtkWidget *labelFrameBox1;
extern GtkWidget *labelFrameBox2;

void calcButtonClick(void);
void gtkWindowInit(int argc, char *argv[]);
