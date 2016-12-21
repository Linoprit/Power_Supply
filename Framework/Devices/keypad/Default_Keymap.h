
const uint8_t default_keypmap_3x4_cols  = 3;
const uint8_t default_keypmap_3x4_rows  = 4;
const unsigned char default_keypmap_3x4[4][3]  =
{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};


// keycodes taken from:
//http://www.csee.umbc.edu/portal/help/theory/ascii.txt

#define  KEY_ESCAPE       0x01	// 1
#define  KEY_BACKSPACE    0x1E	// 30
#define  KEY_HOME         0x20  // 32
#define  KEY_PAGE_UP      0x21  // 33
#define  KEY_DELETE       0x34  // 52
#define  KEY_PAGE_DOWN    0x36  // 54
#define  KEY_ENTER        0x47  // 71
#define  KEY_UP_ARROW     0x57  // 87
#define  KEY_SPACE        0x5E  // 94
#define  KEY_LEFT_ARROW   0x61  // 97
#define  KEY_DOWN_ARROW   0x62  // 98
#define  KEY_RIGHT_ARROW  0x63  // 99

const uint8_t default_commandmap_3x4_cols  = 3;
const uint8_t default_commandmap_3x4_rows  = 4;
const unsigned char default_commandmap_3x4[4][3] =
{
    {KEY_HOME,       KEY_UP_ARROW,   KEY_PAGE_UP},
    {KEY_LEFT_ARROW, KEY_SPACE,      KEY_RIGHT_ARROW},
    {KEY_ESCAPE,     KEY_DOWN_ARROW, KEY_PAGE_DOWN},
    {KEY_DELETE,     KEY_BACKSPACE,  KEY_ENTER}
};
