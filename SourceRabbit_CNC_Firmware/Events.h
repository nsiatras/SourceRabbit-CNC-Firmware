#define EVENT_LIMIT_SWITCH_ON 1
#define EVENT_LIMIT_SWITCH_OFF 2
#define EVENT_TOUCH_PROBE_ON 3
#define EVENT_TOUCH_PROBE_OFF 4
#define EVENT_ERROR_SERIAL_BUFFER_OVVERRUN 5

#ifdef SHOW_DEBUG_MESSAGES
// This method is used only for debug purposes
String getEventNameFromID(int id)
{
    switch (id)
    {
    case EVENT_LIMIT_SWITCH_ON:
        return "EVENT_LIMIT_SWITCH_ON";
        break;

    case EVENT_LIMIT_SWITCH_OFF:
        return "EVENT_LIMIT_SWITCH_OFF";
        break;

    case EVENT_TOUCH_PROBE_ON:
        return "EVENT_TOUCH_PROBE_ON";
        break;

    case EVENT_TOUCH_PROBE_OFF:
        return "EVENT_TOUCH_PROBE_OFF";
        break;

    default:
        return "UNKNOWN EVENT";
        break;
    }
}
#endif