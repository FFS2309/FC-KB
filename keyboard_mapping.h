static int columns[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static int rows[] = {14, 16, 17, 18, 19, 20, 21, 22, 26, 27};
//1,4,5,7
static int num_lock = 25;
static int caps_lock = 11;
static int scroll_lock = 13;

static char* mapping[sizeof(columns)/sizeof(int)][sizeof(rows)/sizeof(int)] = {
	{"^", "--tab", "--caps-lock", "--left-shift", "--left-ctrl", "<", "a", "q", "1", "2"},//column 0
	{"w", "s", "y", "--left-meta", "--left-alt", "x", "d", "e", "3", "4"},
	{"r", "f", "c", "--spacebar", "v", "g", "t", "5", "6", "z"},
	{"h", "b", "n", "j", "u", "7", "8", "i", "k", "m"},
	{",", "l", "o", "9", "0", "p", "ö", ".", "--right-alt", "--right-meta"},
	{"-", "ä", "ü", "ß", "´", "--bckspc", "--return", "+", "#", "--right-shift"},
	{"--application", "--right-ctrl", "--f10", "--f11", "--f12", "0", "0", "0", "0", "0"},
	{"--left", "--down", "--right", "--up", "--del", "--end", "--pagedown", "--pageup", "--home", "--insert"},
	{"--kp-0", "--kp-1", "--kp-2", "--kp-3", "--kp-4", "--kp-5", "--kp-6", "--kp-7", "--kp-8", "--kp-9"},
	{"--kp--enter", "--kp-plus", "--kp-minus", "--kp-mul", "--kp-div", "--num-lock", "0", "0", "0", "0"},
	{"--esc", "--f1", "--f2", "--f3", "--f4", "--f5", "--f6", "--f7", "--f8", "--f9"}//column 10
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
	{.opt = "u", .val = 0xA0},
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
	{.opt = "x", .val = 0x2B},
	{.opt = "c", .val = 0x06},
	{.opt = "v", .val = 0x19},
	{.opt = "b", .val = 0x05},
	{.opt = "n", .val = 0x11},
	{.opt = "m", .val = 0x10},
	{.opt = ",", .val = 0x36},
	{.opt = ".", .val = 0x17},
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
	{.opt = NULL}
};
