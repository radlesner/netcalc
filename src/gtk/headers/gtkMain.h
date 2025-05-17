#include <arpa/inet.h>
#include <errno.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <ifaddrs.h>
#include <locale.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pango/pango.h>
#include <pango/pangocairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define VERSION_PROGRAM "4.1.1"

extern GtkWidget *entryIpAddress;
extern GtkWidget *entryMaskPrefix;
extern GtkWidget *labelFrameBox1;
extern GtkWidget *labelFrameBox2;
extern GtkWidget *labelFrameInterfaceConfigOutput;
extern GtkWidget *labelFrameDnsConfig;

void calcButtonClick(void);
void gtkWindowInit(int argc, char *argv[]);
