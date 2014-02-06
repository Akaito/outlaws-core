
#ifndef EVENT_H
#define EVENT_H


struct Event {
    // !!! KEEP IN SYNC WITH Outlaws.h VERSION !!!
    enum Type { KEY_DOWN=0, KEY_UP, MOUSE_DOWN, MOUSE_UP, MOUSE_DRAGGED, MOUSE_MOVED, SCROLL_WHEEL, LOST_FOCUS, GAINED_FOCUS };
    Type   type;
    long   key;
    long   rawkey;
    float2 pos;
    float2 vel;
    float  delta;  
};

enum {
    NSEnterCharacter                = 0x0003,
    NSBackspaceCharacter            = 0x0008,
    NSTabCharacter                  = 0x0009,
    NSNewlineCharacter              = 0x000a,
    NSFormFeedCharacter             = 0x000c,
    NSCarriageReturnCharacter       = 0x000d,
    EscapeCharacter                 = '\033',
    NSBackTabCharacter              = 0x0019,
    NSDeleteCharacter               = 0x007f,
    NSLineSeparatorCharacter        = 0x2028,
    NSParagraphSeparatorCharacter   = 0x2029,

    NSUpArrowFunctionKey = 0xF700,
    NSDownArrowFunctionKey = 0xF701,
    NSLeftArrowFunctionKey = 0xF702,
    NSRightArrowFunctionKey = 0xF703,
    NSF1FunctionKey = 0xF704,
    NSF2FunctionKey = 0xF705,
    NSF3FunctionKey = 0xF706,
    NSF4FunctionKey = 0xF707,
    NSF5FunctionKey = 0xF708,
    NSF6FunctionKey = 0xF709,
    NSF7FunctionKey = 0xF70A,
    NSF8FunctionKey = 0xF70B,
    NSF9FunctionKey = 0xF70C,
    NSF10FunctionKey = 0xF70D,
    NSF11FunctionKey = 0xF70E,
    NSF12FunctionKey = 0xF70F,
    NSF13FunctionKey = 0xF710,
    NSF14FunctionKey = 0xF711,
    NSF15FunctionKey = 0xF712,
    NSF16FunctionKey = 0xF713,
    NSF17FunctionKey = 0xF714,
    NSF18FunctionKey = 0xF715,
    NSF19FunctionKey = 0xF716,
    NSF20FunctionKey = 0xF717,
    NSF21FunctionKey = 0xF718,
    NSF22FunctionKey = 0xF719,
    NSF23FunctionKey = 0xF71A,
    NSF24FunctionKey = 0xF71B,
    NSF25FunctionKey = 0xF71C,
    NSF26FunctionKey = 0xF71D,
    NSF27FunctionKey = 0xF71E,
    NSF28FunctionKey = 0xF71F,
    NSF29FunctionKey = 0xF720,
    NSF30FunctionKey = 0xF721,
    NSF31FunctionKey = 0xF722,
    NSF32FunctionKey = 0xF723,
    NSF33FunctionKey = 0xF724,
    NSF34FunctionKey = 0xF725,
    NSF35FunctionKey = 0xF726,
    NSInsertFunctionKey = 0xF727,
    NSDeleteFunctionKey = 0xF728,
    NSHomeFunctionKey = 0xF729,
    NSBeginFunctionKey = 0xF72A,
    NSEndFunctionKey = 0xF72B,
    NSPageUpFunctionKey = 0xF72C,
    NSPageDownFunctionKey = 0xF72D,
    NSPrintScreenFunctionKey = 0xF72E,
    NSScrollLockFunctionKey = 0xF72F,
    NSPauseFunctionKey = 0xF730,
    NSSysReqFunctionKey = 0xF731,
    NSBreakFunctionKey = 0xF732,
    NSResetFunctionKey = 0xF733,
    NSStopFunctionKey = 0xF734,
    NSMenuFunctionKey = 0xF735,
    NSUserFunctionKey = 0xF736,
    NSSystemFunctionKey = 0xF737,
    NSPrintFunctionKey = 0xF738,
    NSClearLineFunctionKey = 0xF739,
    NSClearDisplayFunctionKey = 0xF73A,
    NSInsertLineFunctionKey = 0xF73B,
    NSDeleteLineFunctionKey = 0xF73C,
    NSInsertCharFunctionKey = 0xF73D,
    NSDeleteCharFunctionKey = 0xF73E,
    NSPrevFunctionKey = 0xF73F,
    NSNextFunctionKey = 0xF740,
    NSSelectFunctionKey = 0xF741,
    NSExecuteFunctionKey = 0xF742,
    NSUndoFunctionKey = 0xF743,
    NSRedoFunctionKey = 0xF744,
    NSFindFunctionKey = 0xF745,
    NSHelpFunctionKey = 0xF746,
    NSModeSwitchFunctionKey = 0xF747,

    LeftMouseButton = 0xF748,
    RightMouseButton = 0xF749,
    MiddleMouseButton = 0xF74A,

    // OShiftKey, OControlKey, and OAltKey from Outlaws.h go here

    SpecialKeyCount = 0xF74E,
};


class KeyState {
    bool ascii[256];
    bool function[SpecialKeyCount - NSUpArrowFunctionKey];
    bool misc;
    
public:
    KeyState()
    {
        reset();
    }
    
    bool& operator[](int c)
    {
        if (0 <= c && c < 256)
            return ascii[c];
        if (NSUpArrowFunctionKey <= c && c < SpecialKeyCount)
            return function[c - NSUpArrowFunctionKey];
        else
            ASSERT(0);
        return misc;
    }

    bool operator[](int c) const
    {
        return (*const_cast<KeyState*>(this))[c];
    }

    void reset()
    {
        memset(ascii, false, sizeof(ascii));
        memset(function, false, sizeof(function));
        misc = false;
    }

    void cancelMouseDown()
    {
        (*this)[0 + LeftMouseButton] = false;
        (*this)[1 + LeftMouseButton] = false;
        (*this)[2 + LeftMouseButton] = false;
    }

};

inline string keyToString(int key)
{
    switch (key) 
    {
    case LeftMouseButton: return "Left Mouse";
    case RightMouseButton: return "Right Mouse";
    case MiddleMouseButton: return "Middle Mouse";
    case NSUpArrowFunctionKey: return "Up";
    case NSDownArrowFunctionKey: return "Down";
    case NSRightArrowFunctionKey: return "Right";
    case NSLeftArrowFunctionKey: return "Left";
    case OShiftKey: return "Shift";
    case OControlKey: return "Control";
    case OAltKey: return "Alt";
    case '\t': return "Tab";
    case '\r': return "Enter";
    case ' ': return "Space";
    case NSPageUpFunctionKey: return "Page Up";
    case NSPageDownFunctionKey: return "Page Down";
    case NSDeleteCharacter: return "Delete";
    case NSBackspaceCharacter: return "Backspace";
    case EscapeCharacter: return "Escape";
    case 0: return " ";
    default:
        if (isprint(key))
            return str_format("'%c'", key);
        else
            return str_format("0x%x", key);
    }
}


#endif // EVENT_H
