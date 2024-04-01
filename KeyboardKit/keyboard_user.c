/*
 * keyboard_user.c
 *
 *  Created on: Mar 17, 2024
 *      Author: xq123
 */
#include "keyboard.h"
#include "rgb.h"
#include "usbd_conf.h"
#include "usb_device.h"
#include "usbd_custom_hid_if.h"

const uint16_t g_default_keymap[LAYER_NUM][ADVANCED_KEY_NUM + KEY_NUM] = {
    {
        ESC/*0*/, NUM_1/*1*/, NUM_2/*2*/, NUM_3/*3*/, NUM_4/*4*/, NUM_5/*5*/, NUM_6/*6*/, NUM_7/*7*/, NUM_8/*8*/, NUM_9/*9*/, NUM_0/*10*/, MINUS/*11*/, EQUAL/*12*/, BACKSPACE/*13*/,
        TAB/*14*/, Q/*15*/, W/*16*/, E/*17*/, R/*18*/, T/*19*/, Y/*20*/, U/*21*/, I/*22*/, O/*23*/, P/*24*/, LEFT_U_BRACE/*25*/, RIGHT_U_BRACE/*26*/, BACKSLASH/*27*/,
        CAP_LOCK/*28*/, A/*29*/, S/*30*/, D/*31*/, F/*32*/, G/*33*/, H/*34*/, J/*35*/, K/*36*/, L/*37*/, SEMI_COLON/*38*/, QUOTE/*39*/, ENTER/*40*/,
        LEFT_SHIFT/*41*/, Z/*42*/, X/*43*/, C/*44*/, V/*45*/, B/*46*/, N/*47*/, M/*48*/, COMMA/*49*/, PERIOD/*50*/, SLASH/*51*/, RIGHT_SHIFT/*52*/, UP_ARROW/*53*/, DELETE/*54*/,
        LEFT_CTRL/*55*/, LEFT_GUI/*56*/, LEFT_ALT/*57*/, SPACE/*58*/, RIGHT_ALT/*59*/, FN/*60*/, LEFT_ARROW/*61*/, DOWN_ARROW/*62*/, RIGHT_ARROW/*63*/,
    },

    {
        GRAVE_ACCENT, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, BACKSPACE,
        TAB, PROFILE1, PROFILE2, PROFILE3, PROFILE4, T, Y, U, I, O, P, LEFT_U_BRACE, RIGHT_U_BRACE, BACKSLASH,
        CAP_LOCK, A, S, D, F, G, H, J, K, L, SEMI_COLON, QUOTE, ENTER,
        LEFT_SHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RIGHT_SHIFT, UP_ARROW, DELETE,
        LEFT_CTRL, LEFT_GUI, LEFT_ALT, SPACE, RIGHT_ALT, FN, LEFT_ARROW, DOWN_ARROW, RIGHT_ARROW,
    }

};

const uint8_t g_rgb_mapping[ADVANCED_KEY_NUM]={26,25,24,23,9,10,11,12,36,37,38,39,53,52,51,50,
                                             35,34,33,32,19,20,21,22,46,47,48,49,63,62,61,60,
                                             3,15,29,42,41,56,28,14,13,27,40,55,54,0,1,2,
                                             4,5,6,7,8,18,17,31,44,45,59,58,16,30,43,57};
const RGBLocation g_rgb_locations[RGB_NUM]={{0,0.625},{0,1.875},{0,3.125},{0,6.875},{0,10.5},{0,11.5},{0,12.5},{0,13.5},{0,14.5},
                                             {1,1},{1,2.5},{1,3.5},{1,4.5},{1,5.5},{1,6.5},{1,7.5},{1,8.5},{1,9.5},{1,10.5},{1,11.5},{1,12.5},{1,13.5},{1,14.5},
                                             {2,0.875},{2,2.25},{2,3.25},{2,4.25},{2,5.25},{2,6.25},{2,7.25},{2,8.25},{2,9.25},{2,10.25},{2,11.25},{2,12.25},{2,13.875},
                                             {3,0.75},{3,2},{3,3},{3,4},{3,5},{3,6},{3,7},{3,8},{3,9},{3,10},{3,11},{3,12},{3,13},{3,14.25},
                                             {4,0.5},{4,1.5},{4,2.5},{4,3.5},{4,4.5},{4,5.5},{4,6.5},{4,7.5},{4,8.5},{4,9.5},{4,10.5},{4,11.5},{4,12.5},{4,14}};

AdvancedKey g_keyboard_advanced_keys[ADVANCED_KEY_NUM] =
{
    //Group 1 Begin
    {.key.id = 31},
    {.key.id = 30},
    {.key.id = 29},
    {.key.id = 28},
    {.key.id = 41}, //Left Shift
    {.key.id = 42},
    {.key.id = 43},
    {.key.id = 44},//C
    {.key.id = 14},
    {.key.id = 15},
    {.key.id = 16},
    {.key.id = 17},
    {.key.id = 3},
    {.key.id = 2},
    {.key.id = 1},
    {.key.id = 0},
    //Group 2 Begin
    {.key.id = 40},
    {.key.id = 39},
    {.key.id = 38},
    {.key.id = 37},
    {.key.id = 51},
    {.key.id = 52}, //Right Shift
    {.key.id = 53},
    {.key.id = 54},
    {.key.id = 24},
    {.key.id = 25},
    {.key.id = 26},
    {.key.id = 27},
    {.key.id = 13},
    {.key.id = 12},
    {.key.id = 11},
    {.key.id = 10},
    //Group 3 Begin
    {.key.id = 58},
    {.key.id = 47},
    {.key.id = 34},
    {.key.id = 20},
    {.key.id = 19},
    {.key.id = 6},
    {.key.id = 33},
    {.key.id = 46},
    {.key.id = 45},//V
    {.key.id = 32},
    {.key.id = 18},
    {.key.id = 5},
    {.key.id = 4},
    {.key.id = 55}, //Left Control
    {.key.id = 56}, //Left GUI
    {.key.id = 57}, //Left Alt
    //Group 4 Begin
    {.key.id = 59}, //Right alt
    {.key.id = 60}, //Fn
    {.key.id = 61},
    {.key.id = 62},
    {.key.id = 63},
    {.key.id = 50},
    {.key.id = 49},
    {.key.id = 36},
    {.key.id = 22},
    {.key.id = 23},
    {.key.id = 9},
    {.key.id = 8},
    {.key.id = 48},
    {.key.id = 35},
    {.key.id = 21},
    {.key.id = 7}
};

static const float table[]=
{
    0.000000,
    0.002222,
    0.004444,
    0.006667,
    0.008889,
    0.011111,
    0.013333,
    0.015556,
    0.017778,
    0.020000,
    0.022222,
    0.024444,
    0.026667,
    0.028889,
    0.031111,
    0.033333,
    0.035556,
    0.037778,
    0.040000,
    0.042222,
    0.044444,
    0.046667,
    0.048889,
    0.051111,
    0.053333,
    0.055556,
    0.057778,
    0.060000,
    0.062222,
    0.064444,
    0.066667,
    0.068889,
    0.071111,
    0.073333,
    0.075556,
    0.077778,
    0.080000,
    0.082222,
    0.084444,
    0.086667,
    0.088889,
    0.091111,
    0.093333,
    0.095556,
    0.097778,
    0.100000,
    0.102222,
    0.104444,
    0.106667,
    0.108889,
    0.111111,
    0.113333,
    0.115556,
    0.117778,
    0.120000,
    0.122222,
    0.124444,
    0.126667,
    0.128889,
    0.131111,
    0.133333,
    0.135556,
    0.137778,
    0.140000,
    0.142222,
    0.144444,
    0.146667,
    0.148889,
    0.151111,
    0.153333,
    0.155556,
    0.157778,
    0.160000,
    0.162222,
    0.164444,
    0.166667,
    0.168889,
    0.171111,
    0.173333,
    0.175556,
    0.177778,
    0.180000,
    0.182222,
    0.184444,
    0.186667,
    0.188889,
    0.191111,
    0.193333,
    0.195556,
    0.197778,
    0.200000,
    0.202222,
    0.204444,
    0.206667,
    0.208889,
    0.211111,
    0.213333,
    0.215556,
    0.217778,
    0.220000,
    0.222222,
    0.224444,
    0.226667,
    0.228889,
    0.231111,
    0.233333,
    0.235556,
    0.237778,
    0.240000,
    0.242222,
    0.244444,
    0.246667,
    0.248889,
    0.251111,
    0.253333,
    0.255556,
    0.257778,
    0.260000,
    0.262222,
    0.264444,
    0.266667,
    0.268889,
    0.271111,
    0.273333,
    0.275556,
    0.277778,
    0.280000,
    0.282222,
    0.284444,
    0.286667,
    0.288889,
    0.291111,
    0.293333,
    0.295556,
    0.297778,
    0.300000,
    0.302222,
    0.304444,
    0.306667,
    0.308889,
    0.311111,
    0.313333,
    0.315556,
    0.317778,
    0.320000,
    0.322222,
    0.324444,
    0.326667,
    0.328889,
    0.331111,
    0.333333,
    0.335556,
    0.337778,
    0.340000,
    0.342222,
    0.344444,
    0.346667,
    0.348889,
    0.351111,
    0.353333,
    0.355556,
    0.357778,
    0.360000,
    0.362222,
    0.364444,
    0.366667,
    0.368889,
    0.371111,
    0.373333,
    0.375556,
    0.377778,
    0.380000,
    0.382222,
    0.384444,
    0.386667,
    0.388889,
    0.391111,
    0.393333,
    0.395556,
    0.397778,
    0.400000,
    0.402222,
    0.404444,
    0.406667,
    0.408889,
    0.411111,
    0.413333,
    0.415556,
    0.417778,
    0.420000,
    0.422222,
    0.424444,
    0.426667,
    0.428889,
    0.431111,
    0.433333,
    0.435556,
    0.437778,
    0.440000,
    0.442222,
    0.444444,
    0.446667,
    0.448889,
    0.451111,
    0.453333,
    0.455556,
    0.457778,
    0.460000,
    0.462222,
    0.464444,
    0.466667,
    0.468889,
    0.471111,
    0.473333,
    0.475556,
    0.477778,
    0.480000,
    0.482222,
    0.484444,
    0.486667,
    0.488889,
    0.491111,
    0.493333,
    0.495556,
    0.497778,
    0.500000,
    0.501397,
    0.502793,
    0.504190,
    0.505587,
    0.506983,
    0.508380,
    0.509777,
    0.511173,
    0.512570,
    0.513967,
    0.515363,
    0.516760,
    0.518156,
    0.519553,
    0.520950,
    0.522346,
    0.523743,
    0.525140,
    0.526536,
    0.527933,
    0.529330,
    0.530726,
    0.532123,
    0.533520,
    0.534916,
    0.536313,
    0.537709,
    0.539106,
    0.540503,
    0.541899,
    0.543296,
    0.544693,
    0.546089,
    0.547486,
    0.548883,
    0.550279,
    0.551676,
    0.553073,
    0.554469,
    0.555866,
    0.557263,
    0.558659,
    0.560056,
    0.561453,
    0.562849,
    0.564246,
    0.565642,
    0.567039,
    0.568436,
    0.569832,
    0.571229,
    0.572626,
    0.574022,
    0.575419,
    0.576816,
    0.578212,
    0.579609,
    0.581006,
    0.582402,
    0.583799,
    0.585196,
    0.586592,
    0.587989,
    0.589386,
    0.590782,
    0.592179,
    0.593575,
    0.594972,
    0.596369,
    0.597765,
    0.599162,
    0.600559,
    0.601955,
    0.603352,
    0.604749,
    0.606145,
    0.607542,
    0.608939,
    0.610335,
    0.611732,
    0.613128,
    0.614525,
    0.615922,
    0.617318,
    0.618715,
    0.620112,
    0.621508,
    0.622905,
    0.624302,
    0.625698,
    0.627095,
    0.628492,
    0.629888,
    0.631285,
    0.632682,
    0.634078,
    0.635475,
    0.636872,
    0.638268,
    0.639665,
    0.641061,
    0.642458,
    0.643855,
    0.645251,
    0.646648,
    0.648045,
    0.649441,
    0.650838,
    0.652235,
    0.653631,
    0.655028,
    0.656425,
    0.657821,
    0.659218,
    0.660615,
    0.662011,
    0.663408,
    0.664804,
    0.666201,
    0.667598,
    0.668994,
    0.670391,
    0.671788,
    0.673184,
    0.674581,
    0.675978,
    0.677374,
    0.678771,
    0.680168,
    0.681564,
    0.682961,
    0.684358,
    0.685754,
    0.687151,
    0.688547,
    0.689944,
    0.691341,
    0.692737,
    0.694134,
    0.695531,
    0.696927,
    0.698324,
    0.699721,
    0.701117,
    0.702514,
    0.703911,
    0.705307,
    0.706704,
    0.708101,
    0.709497,
    0.710894,
    0.712291,
    0.713687,
    0.715084,
    0.716480,
    0.717877,
    0.719274,
    0.720670,
    0.722067,
    0.723464,
    0.724860,
    0.726257,
    0.727654,
    0.729050,
    0.730447,
    0.731844,
    0.733240,
    0.734637,
    0.736033,
    0.737430,
    0.738827,
    0.740223,
    0.741620,
    0.743017,
    0.744413,
    0.745810,
    0.747207,
    0.748603,
    0.750000,
    0.750419,
    0.750839,
    0.751258,
    0.751678,
    0.752097,
    0.752517,
    0.752936,
    0.753356,
    0.753775,
    0.754195,
    0.754614,
    0.755034,
    0.755453,
    0.755872,
    0.756292,
    0.756711,
    0.757131,
    0.757550,
    0.757970,
    0.758389,
    0.758809,
    0.759228,
    0.759648,
    0.760067,
    0.760487,
    0.760906,
    0.761325,
    0.761745,
    0.762164,
    0.762584,
    0.763003,
    0.763423,
    0.763842,
    0.764262,
    0.764681,
    0.765101,
    0.765520,
    0.765940,
    0.766359,
    0.766779,
    0.767198,
    0.767617,
    0.768037,
    0.768456,
    0.768876,
    0.769295,
    0.769715,
    0.770134,
    0.770554,
    0.770973,
    0.771393,
    0.771812,
    0.772232,
    0.772651,
    0.773070,
    0.773490,
    0.773909,
    0.774329,
    0.774748,
    0.775168,
    0.775587,
    0.776007,
    0.776426,
    0.776846,
    0.777265,
    0.777685,
    0.778104,
    0.778524,
    0.778943,
    0.779362,
    0.779782,
    0.780201,
    0.780621,
    0.781040,
    0.781460,
    0.781879,
    0.782299,
    0.782718,
    0.783138,
    0.783557,
    0.783976,
    0.784396,
    0.784815,
    0.785235,
    0.785654,
    0.786074,
    0.786493,
    0.786913,
    0.787332,
    0.787752,
    0.788171,
    0.788591,
    0.789010,
    0.789430,
    0.789849,
    0.790268,
    0.790688,
    0.791107,
    0.791527,
    0.791946,
    0.792366,
    0.792785,
    0.793205,
    0.793624,
    0.794044,
    0.794463,
    0.794883,
    0.795302,
    0.795721,
    0.796141,
    0.796560,
    0.796980,
    0.797399,
    0.797819,
    0.798238,
    0.798658,
    0.799077,
    0.799497,
    0.799916,
    0.800336,
    0.800755,
    0.801175,
    0.801594,
    0.802013,
    0.802433,
    0.802852,
    0.803272,
    0.803691,
    0.804111,
    0.804530,
    0.804950,
    0.805369,
    0.805789,
    0.806208,
    0.806628,
    0.807047,
    0.807466,
    0.807886,
    0.808305,
    0.808725,
    0.809144,
    0.809564,
    0.809983,
    0.810403,
    0.810822,
    0.811242,
    0.811661,
    0.812081,
    0.812500,
    0.812919,
    0.813339,
    0.813758,
    0.814178,
    0.814597,
    0.815017,
    0.815436,
    0.815856,
    0.816275,
    0.816695,
    0.817114,
    0.817534,
    0.817953,
    0.818372,
    0.818792,
    0.819211,
    0.819631,
    0.820050,
    0.820470,
    0.820889,
    0.821309,
    0.821728,
    0.822148,
    0.822567,
    0.822987,
    0.823406,
    0.823825,
    0.824245,
    0.824664,
    0.825084,
    0.825503,
    0.825923,
    0.826342,
    0.826762,
    0.827181,
    0.827601,
    0.828020,
    0.828440,
    0.828859,
    0.829279,
    0.829698,
    0.830117,
    0.830537,
    0.830956,
    0.831376,
    0.831795,
    0.832215,
    0.832634,
    0.833054,
    0.833473,
    0.833893,
    0.834312,
    0.834732,
    0.835151,
    0.835570,
    0.835990,
    0.836409,
    0.836829,
    0.837248,
    0.837668,
    0.838087,
    0.838507,
    0.838926,
    0.839346,
    0.839765,
    0.840185,
    0.840604,
    0.841024,
    0.841443,
    0.841862,
    0.842282,
    0.842701,
    0.843121,
    0.843540,
    0.843960,
    0.844379,
    0.844799,
    0.845218,
    0.845638,
    0.846057,
    0.846476,
    0.846896,
    0.847315,
    0.847735,
    0.848154,
    0.848574,
    0.848993,
    0.849413,
    0.849832,
    0.850252,
    0.850671,
    0.851091,
    0.851510,
    0.851930,
    0.852349,
    0.852768,
    0.853188,
    0.853607,
    0.854027,
    0.854446,
    0.854866,
    0.855285,
    0.855705,
    0.856124,
    0.856544,
    0.856963,
    0.857383,
    0.857802,
    0.858221,
    0.858641,
    0.859060,
    0.859480,
    0.859899,
    0.860319,
    0.860738,
    0.861158,
    0.861577,
    0.861997,
    0.862416,
    0.862836,
    0.863255,
    0.863675,
    0.864094,
    0.864513,
    0.864933,
    0.865352,
    0.865772,
    0.866191,
    0.866611,
    0.867030,
    0.867450,
    0.867869,
    0.868289,
    0.868708,
    0.869128,
    0.869547,
    0.869966,
    0.870386,
    0.870805,
    0.871225,
    0.871644,
    0.872064,
    0.872483,
    0.872903,
    0.873322,
    0.873742,
    0.874161,
    0.874581,
    0.875000,
    0.875419,
    0.875839,
    0.876258,
    0.876678,
    0.877097,
    0.877517,
    0.877936,
    0.878356,
    0.878775,
    0.879195,
    0.879614,
    0.880034,
    0.880453,
    0.880872,
    0.881292,
    0.881711,
    0.882131,
    0.882550,
    0.882970,
    0.883389,
    0.883809,
    0.884228,
    0.884648,
    0.885067,
    0.885487,
    0.885906,
    0.886325,
    0.886745,
    0.887164,
    0.887584,
    0.888003,
    0.888423,
    0.888842,
    0.889262,
    0.889681,
    0.890101,
    0.890520,
    0.890940,
    0.891359,
    0.891779,
    0.892198,
    0.892617,
    0.893037,
    0.893456,
    0.893876,
    0.894295,
    0.894715,
    0.895134,
    0.895554,
    0.895973,
    0.896393,
    0.896812,
    0.897232,
    0.897651,
    0.898070,
    0.898490,
    0.898909,
    0.899329,
    0.899748,
    0.900168,
    0.900587,
    0.901007,
    0.901426,
    0.901846,
    0.902265,
    0.902685,
    0.903104,
    0.903524,
    0.903943,
    0.904362,
    0.904782,
    0.905201,
    0.905621,
    0.906040,
    0.906460,
    0.906879,
    0.907299,
    0.907718,
    0.908138,
    0.908557,
    0.908976,
    0.909396,
    0.909815,
    0.910235,
    0.910654,
    0.911074,
    0.911493,
    0.911913,
    0.912332,
    0.912752,
    0.913171,
    0.913591,
    0.914010,
    0.914430,
    0.914849,
    0.915268,
    0.915688,
    0.916107,
    0.916527,
    0.916946,
    0.917366,
    0.917785,
    0.918205,
    0.918624,
    0.919044,
    0.919463,
    0.919883,
    0.920302,
    0.920721,
    0.921141,
    0.921560,
    0.921980,
    0.922399,
    0.922819,
    0.923238,
    0.923658,
    0.924077,
    0.924497,
    0.924916,
    0.925336,
    0.925755,
    0.926175,
    0.926594,
    0.927013,
    0.927433,
    0.927852,
    0.928272,
    0.928691,
    0.929111,
    0.929530,
    0.929950,
    0.930369,
    0.930789,
    0.931208,
    0.931628,
    0.932047,
    0.932466,
    0.932886,
    0.933305,
    0.933725,
    0.934144,
    0.934564,
    0.934983,
    0.935403,
    0.935822,
    0.936242,
    0.936661,
    0.937081,
    0.937500,
    0.937919,
    0.938339,
    0.938758,
    0.939178,
    0.939597,
    0.940017,
    0.940436,
    0.940856,
    0.941275,
    0.941695,
    0.942114,
    0.942534,
    0.942953,
    0.943372,
    0.943792,
    0.944211,
    0.944631,
    0.945050,
    0.945470,
    0.945889,
    0.946309,
    0.946728,
    0.947148,
    0.947567,
    0.947987,
    0.948406,
    0.948826,
    0.949245,
    0.949664,
    0.950084,
    0.950503,
    0.950923,
    0.951342,
    0.951762,
    0.952181,
    0.952601,
    0.953020,
    0.953440,
    0.953859,
    0.954279,
    0.954698,
    0.955117,
    0.955537,
    0.955956,
    0.956376,
    0.956795,
    0.957215,
    0.957634,
    0.958054,
    0.958473,
    0.958893,
    0.959312,
    0.959732,
    0.960151,
    0.960570,
    0.960990,
    0.961409,
    0.961829,
    0.962248,
    0.962668,
    0.963087,
    0.963507,
    0.963926,
    0.964346,
    0.964765,
    0.965185,
    0.965604,
    0.966024,
    0.966443,
    0.966862,
    0.967282,
    0.967701,
    0.968121,
    0.968540,
    0.968960,
    0.969379,
    0.969799,
    0.970218,
    0.970638,
    0.971057,
    0.971476,
    0.971896,
    0.972315,
    0.972735,
    0.973154,
    0.973574,
    0.973993,
    0.974413,
    0.974832,
    0.975252,
    0.975671,
    0.976091,
    0.976510,
    0.976930,
    0.977349,
    0.977768,
    0.978188,
    0.978607,
    0.979027,
    0.979446,
    0.979866,
    0.980285,
    0.980705,
    0.981124,
    0.981544,
    0.981963,
    0.982383,
    0.982802,
    0.983221,
    0.983641,
    0.984060,
    0.984480,
    0.984899,
    0.985319,
    0.985738,
    0.986158,
    0.986577,
    0.986997,
    0.987416,
    0.987836,
    0.988255,
    0.988675,
    0.989094,
    0.989513,
    0.989933,
    0.990352,
    0.990772,
    0.991191,
    0.991611,
    0.992030,
    0.992450,
    0.992869,
    0.993289,
    0.993708,
    0.994128,
    0.994547,
    0.994966,
    0.995386,
    0.995805,
    0.996225,
    0.996644,
    0.997064,
    0.997483,
    0.997903,
    0.998322,
    0.998742,
    0.999161,
    0.999581,
    1.000000
};

void keyboard_hid_send(uint8_t*report,uint16_t len)
{
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,g_keyboard_report_buffer,17+1);
}


float advanced_key_normalize(AdvancedKey* key, float value)
{
    float x = (key->upper_bound - value) / (key->upper_bound - key->lower_bound);
    uint16_t index = x * 1000.0f;
    if (index < 1000)
        return table[index];
    if (index > 5000)
        return 0;
    return 1.1;
    /*
    if (x<0.225)
    {
        return x*(0.5/0.225);
    }
    else if (x<0.404)
    {
        return (x-0.225)*(0.25/(0.404-0.225))+0.5;
    }
    else
    {
        return (x-0.404)*(0.25/(1.0-0.404))+0.75;
    }
    */
    
}
void keyboard_post_process()
{
}
