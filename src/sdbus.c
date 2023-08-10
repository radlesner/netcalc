#include "headers/sdbus.h"

// -------------------------------------------------------------
int isSDBUSavailable(void)
{
    sd_bus_error dbusErr = SD_BUS_ERROR_NULL;
    sd_bus_message *msg  = NULL;
    sd_bus *dbus         = NULL;

    int err = sd_bus_open_system(&dbus);
    if (err < 0)
    {
        // fprintf(stderr, "can't connect to system D-Bus: %s\n", strerror(-err));
        return 0;
    }

    err = sd_bus_get_property(dbus, "org.freedesktop.resolve1", "/org/freedesktop/resolve1", "org.freedesktop.resolve1.Manager", "DNS", &dbusErr, &msg, "a(iiay)");
    if (err < 0)
    {
        // fprintf(stderr, "can't connect to systemd-resolved: %s\n", dbusErr.message);
        sd_bus_error_free(&dbusErr);
        sd_bus_unref(dbus);
        return 0;
    }

    err = sd_bus_message_enter_container(msg, SD_BUS_TYPE_ARRAY, "(iiay)");
    if (err < 0)
    {
        // fprintf(stderr, "error entering array container: %s\n", strerror(-err));
        sd_bus_message_unref(msg);
        sd_bus_unref(dbus);
        return 0;
    }

    sd_bus_message_exit_container(msg);
    sd_bus_message_unref(msg);
    sd_bus_unref(dbus);

    return 1;
}

// -------------------------------------------------------------
void getSDBUS_dns_IP_address(char SDBUSoutput[])
{
    sd_bus_error dbusErr = SD_BUS_ERROR_NULL;
    sd_bus_message *msg  = NULL;
    sd_bus *dbus         = NULL;

    int32_t netif;
    int32_t af;
    size_t n;
    const void *addr;
    char buf[64];
    int err;

    err = sd_bus_open_system(&dbus);
    if (err < 0)
    {
        // fprintf(stderr, "can't connect to system D-Bus: %s\n", strerror(-err));
        return;
    }

    err = sd_bus_get_property(dbus, "org.freedesktop.resolve1", "/org/freedesktop/resolve1", "org.freedesktop.resolve1.Manager", "DNS", &dbusErr, &msg, "a(iiay)");
    if (err < 0)
    {
        // fprintf(stderr, "can't connect to systemd-resolved: %s\n", dbusErr.message);
        sd_bus_error_free(&dbusErr);
        sd_bus_unref(dbus);
        return;
    }

    err = sd_bus_message_enter_container(msg, SD_BUS_TYPE_ARRAY, "(iiay)");
    if (err < 0)
    {
        // fprintf(stderr, "error entering array container: %s\n", strerror(-err));
        sd_bus_message_unref(msg);
        sd_bus_unref(dbus);
        return;
    }

    while (sd_bus_message_enter_container(msg, SD_BUS_TYPE_STRUCT, "iiay") > 0)
    {
        err = sd_bus_message_read(msg, "ii", &netif, &af);
        if (err < 0)
        {
            // fprintf(stderr, "error reading struct members: %s\n", strerror(-err));
            sd_bus_message_unref(msg);
            sd_bus_unref(dbus);
            return;
        }
        err = sd_bus_message_read_array(msg, 'y', &addr, &n);
        if (err < 0)
        {
            // fprintf(stderr, "error reading array: %s\n", strerror(-err));
            sd_bus_message_unref(msg);
            sd_bus_unref(dbus);
            return;
        }
        sd_bus_message_exit_container(msg);
        inet_ntop(af, addr, buf, sizeof(buf));

        // ----------------------------------- //
        strcpy(SDBUSoutput, buf);
    }
    sd_bus_message_exit_container(msg);

    sd_bus_message_unref(msg);
    sd_bus_unref(dbus);
}
