static int columns[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static int rows[] = {14, 16, 17, 18, 19, 20, 21, 22, 26, 27, 13};
//1,4,5,7
static int num_lock = 25;
static int caps_lock = 11;
static int scroll_lock = 10;

static char* mapping[sizeof(columns)/sizeof(int)][sizeof(rows)/sizeof(int)] = {
	{"^", "w", "r", "h", ",", "-", "--application", "--kp-0", "--kp-enter", "--media4","--esc"},
	{"--tab", "s", "f", "b", "l", "ä", "--right-ctrl", "--kp-1", "--kp-plus", "--pause","--f1"},
	{"--caps-lock", "y", "c", "n", "o", "ü", "--left", "--kp-2", "--kp-minus", "--scrl-lck", "--f2"},
	{"--left-shift", "--left-meta", "--spacebar", "j", "9", "ß", "--down", "--kp-3", "--kp-mul", "--prtsc", "--f3"},
	{"--left-ctrl", "--left-alt", "v", "u", "0", "´", "--up", "--kp-4", "--kp-div", "--home", "--f4"},
	{"<", "x", "g", "7", "p", "--bckspc", "--right", "--kp-5", "--num-lock", "--insert", "--f5"},
	{"a", "d", "t", "8", "ö", "--return", "--del", "--kp-6", "--kp-comma", /*extra key*/"h e l l o", "--f6"},
	{"q", "e", "5", "i", ".", "+", "--end", "--kp-7", "--media1", "--f12", "--f7"},
	{"1", "3", "6", "k", "--right-alt", "#", "--pagedown", "--kp-8", "--media2", "--f11", "--f8"},
	{"2", "4", "z", "m", "--right-meta", "--right-shift", "--pageup", "--kp-9", "--media3", "--f10", "--f9"}
};

struct options {
	const char *opt;
	unsigned char val;
};

static struct options kmod[] = {
	{.opt = "--left-ctrl", .val = 0x01},
	{.opt = "--right-ctrl", .val = 0x10},
	{.opt = "--left-shift", .val = 0x02},
	{.opt = "--right-shift", .val = 0x20},
	{.opt = "--left-alt", .val = 0x04},
	{.opt = "--right-alt", .val = 0x40},
	{.opt = "--left-meta", .val = 0x08},
	{.opt = "--right-meta", .val = 0x80},
	{.opt = NULL}
};

static struct options kval[] = {
//	{.opt = "--extra", .val = 0x7F},
//	{.opt = "--media1", .val = 0x81}, Media keys are consumer HID not Keyboard HID
//	{.opt = "--media2", .val = 0x80},
//	{.opt = "--media3", .val = 0xCD},
//	{.opt = "--media4", .val = 0xCE},
	{.opt = "^", .val = 0x35},
	{.opt = "1", .val = 0x1E},
	{.opt = "2", .val = 0x1F},
	{.opt = "3", .val = 0x20},
	{.opt = "4", .val = 0x21},
	{.opt = "5", .val = 0x22},
	{.opt = "6", .val = 0x23},
	{.opt = "7", .val = 0x24},
	{.opt = "8", .val = 0x25},
	{.opt = "9", .val = 0x26},
	{.opt = "0", .val = 0x27},
	{.opt = "ß", .val = 0x2D},
	{.opt = "´", .val = 0x2E},
	{.opt = "--bckspc", .val = 0x2A},
	{.opt = "--tab", .val = 0x2B},
	{.opt = "q", .val = 0x14},
	{.opt = "w", .val = 0x1A},
	{.opt = "e", .val = 0x08},
	{.opt = "r", .val = 0x15},
	{.opt = "t", .val = 0x17},
	{.opt = "z", .val = 0x1C},
	{.opt = "u", .val = 0x18},
	{.opt = "i", .val = 0x0C},
	{.opt = "o", .val = 0x12},
	{.opt = "p", .val = 0x13},
	{.opt = "ü", .val = 0x2f},
	{.opt = "+", .val = 0x30},
	{.opt = "--caps-lock", .val = 0x39},
	{.opt = "a", .val = 0x04},
	{.opt = "s", .val = 0x16},
	{.opt = "d", .val = 0x07},
	{.opt = "f", .val = 0x09},
	{.opt = "g", .val = 0x0A},
	{.opt = "h", .val = 0x0B},
	{.opt = "j", .val = 0x0D},
	{.opt = "k", .val = 0x0E},
	{.opt = "l", .val = 0x0F},
	{.opt = "ö", .val = 0x33},
	{.opt = "ä", .val = 0x34},
	{.opt = "#", .val = 0x32},
	{.opt = "--return", .val = 0x28},
	{.opt = "<", .val = 0x64},
	{.opt = "y", .val = 0x1D},
	{.opt = "x", .val = 0x1B},
	{.opt = "c", .val = 0x06},
	{.opt = "v", .val = 0x19},
	{.opt = "b", .val = 0x05},
	{.opt = "n", .val = 0x11},
	{.opt = "m", .val = 0x10},
	{.opt = ",", .val = 0x36},
	{.opt = ".", .val = 0x37},
	{.opt = "-", .val = 0x38},
	{.opt = "--spacebar", .val = 0x2C},
	{.opt = "--esc", .val = 0x29},
	{.opt = "--f1", .val = 0x3a},
	{.opt = "--f2", .val = 0x3b},
	{.opt = "--f3", .val = 0x3c},
	{.opt = "--f4", .val = 0x3d},
	{.opt = "--f5", .val = 0x3e},
	{.opt = "--f6", .val = 0x3f},
	{.opt = "--f7", .val = 0x40},
	{.opt = "--f8", .val = 0x41},
	{.opt = "--f9", .val = 0x42},
	{.opt = "--f10", .val = 0x43},
	{.opt = "--f11", .val = 0x44},
	{.opt = "--f12", .val = 0x45},
	{.opt = "--insert", .val = 0x49},
	{.opt = "--home", .val = 0x4a},
	{.opt = "--pageup", .val = 0x4b},
	{.opt = "--del", .val = 0x4c},
	{.opt = "--end", .val = 0x4d},
	{.opt = "--pagedown", .val = 0x4e},
	{.opt = "--right", .val = 0x4f},
	{.opt = "--left", .val = 0x50},
	{.opt = "--down", .val = 0x51},
	{.opt = "--up", .val = 0x52},
	{.opt = "--application", .val = 0x65},
	{.opt = "--num-lock", .val = 0x53},
	{.opt = "--kp-enter", .val = 0x58},
	{.opt = "--kp-0", .val = 0x62},
	{.opt = "--kp-1", .val = 0x59},
	{.opt = "--kp-2", .val = 0x5A},
	{.opt = "--kp-3", .val = 0x5B},
	{.opt = "--kp-4", .val = 0x5C},
	{.opt = "--kp-5", .val = 0x5D},
	{.opt = "--kp-6", .val = 0x5E},
	{.opt = "--kp-7", .val = 0x5F},
	{.opt = "--kp-8", .val = 0x60},
	{.opt = "--kp-9", .val = 0x61},
	{.opt = "--kp-div", .val = 0x54},
	{.opt = "--kp-mul", .val = 0x55},
	{.opt = "--kp-minus", .val = 0x56},
	{.opt = "--kp-plus", .val = 0x57},
	{.opt = "--kp-comma", .val = 0x63},
	{.opt = "--pause", .val = 0x48},
	{.opt = "--scrl-lck", .val = 0x47},
	{.opt = "--prtsc", .val = 0x46},
	{.opt = NULL}
};
