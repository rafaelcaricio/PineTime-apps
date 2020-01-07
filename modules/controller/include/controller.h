/*
 * Copyright (C) 2018 Koen Zandberg <koen@bergzand.net>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <stdint.h>
#include "event.h"
#include "gui.h"
#include "widget.h"
#include "controller/structs.h"
#include "controller/time.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CONTROLLER_THREAD_FLAG_TICK (1 << 8)

typedef struct control_event_handler control_event_handler_t;

struct control_event_handler {
    struct control_event_handler *next;
    uint32_t events;
    struct _widget *widget;
};

typedef struct {
    event_queue_t queue;
    controller_time_spec_t cur_time;    /* Current time */
    uint32_t last_update;               /* Last RTC counter value */
    bool time_in_sync;                  /* If the time is synced at least once a day */
    gui_screen_t cur_screen;
    widget_t *active_widget;
    control_event_handler_t *handlers;
    kernel_pid_t pid;
} controller_t;

#define CONTROLLER_EVENT_FLAG(flag)     (1 << flag)

controller_t *controller_get(void);

int controller_action_submit_input_action(widget_t *widget,
                                        controller_action_widget_t action);

void controller_add_control_handler(controller_t *controller,
                                    control_event_handler_t *handler);

const controller_time_spec_t *controller_time_get_time(controller_t *controller);
void controller_update_time(controller_t *controller);
void controller_time_set_time(controller_t *controller, controller_time_spec_t *time);

int controller_thread_create(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_CONTROLLER_H */
