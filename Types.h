
#ifndef COSC_ASS_TWO_TYPES
#define COSC_ASS_TWO_TYPES

// Tiles Showing Colour
#define RED_TRUE            "\u001b[91mR\u001b[0m"
#define YELLOW_TRUE         "\u001b[93mY\u001b[0m"
#define DBLUE_TRUE          "\u001b[94mB\u001b[0m"
#define LBLUE_TRUE          "\u001b[96mL\u001b[0m"
#define BLACK_TRUE          "\u001b[90mU\u001b[0m"
#define FIRST_TRUE          "\u001b[97mF\u001b[0m"

// Tiles with colours and symbols
#define RED_SYMBOL          "\u001b[91m\u03C2\u001b[0m" // sigma
#define YELLOW_SYMBOL       "\u001b[93m\u0263\u001b[0m" // gamma
#define DBLUE_SYMBOL        "\u001b[94m\u03B2\u001b[0m" // beta
#define LBLUE_SYMBOL        "\u001b[96m\u03BB\u001b[0m" // lambda
#define BLACK_SYMBOL        "\u001b[90m\u03BC\u001b[0m" // mu
#define FIRST_SYMBOL        "\u001b[97m\u03B1\u001b[0m" // alpha

// Colour codes
#define CRED                'R'
#define CYELLOW             'Y'
#define CDARK_BLUE          'B'
#define CLIGHT_BLUE         'L'
#define CBLACK              'U'
#define cDARK_BLUE          'b'

// Other tile types
#define CFIRST_PLAYER       'F'
#define NO_TILE             '.'

// Global variables
#define FACTORY_MAX_TILES   4
#define BAG_MAX_TILES       100   
#define COMPLETED_GRID_SIZE 5
#define FLOOR_SIZE          7
#define MOSAIC_LEN          25

// Mosaic Rows - Human input version
#define ROW1                1
#define ROW2                2
#define ROW3                3
#define ROW4                4
#define ROW5                5

//Mosaic Rows (and cols) - Index version
#define I1                  0
#define I2                  1
#define I3                  2
#define I4                  3
#define I5                  4

//Printing Mosaic Keys
#define STORAGE1            "1:         "
#define STORAGE2            "2:       "
#define STORAGE3            "3:     "
#define STORAGE4            "4:   "
#define STORAGE5            "5: "
#define BARRIER             "||"

//Loaded lines from savefile
#define NUM_SAVE_FILE_LINES     53

#define LOADED_GAME_FILE        loadedArray[]

#define LOADED_NUMPLAYERS       loadedArray[0]
#define LOADED_TURN             loadedArray[1]

#define LOADED_P1_NAME          loadedArray[2]
#define LOADED_P1_SCORE         loadedArray[3]
#define LOADED_P2_NAME          loadedArray[4]
#define LOADED_P2_SCORE         loadedArray[5]
#define LOADED_P3_NAME          loadedArray[6]
#define LOADED_P3_SCORE         loadedArray[7]
#define LOADED_P4_NAME          loadedArray[8]
#define LOADED_P4_SCORE         loadedArray[9]

#define LOADED_NUMFACTORIES     loadedArray[10]
#define LOADED_FACTORY_0        loadedArray[11]
#define LOADED_FACTORY_00       loadedArray[12]
#define LOADED_FACTORY_1        loadedArray[13]
#define LOADED_FACTORY_2        loadedArray[14]
#define LOADED_FACTORY_3        loadedArray[15]
#define LOADED_FACTORY_4        loadedArray[16]
#define LOADED_FACTORY_5        loadedArray[17]
#define LOADED_FACTORY_6        loadedArray[18]
#define LOADED_FACTORY_7        loadedArray[19]
#define LOADED_FACTORY_8        loadedArray[20]
#define LOADED_FACTORY_9        loadedArray[21]

#define LOADED_P1_WALL_1        loadedArray[22]
#define LOADED_P1_WALL_2        loadedArray[23]
#define LOADED_P1_WALL_3        loadedArray[24]
#define LOADED_P1_WALL_4        loadedArray[25]
#define LOADED_P1_WALL_5        loadedArray[26]
#define LOADED_P1_FLOOR         loadedArray[27]
#define LOADED_P1_MOSAIC        loadedArray[28]

#define LOADED_P2_WALL_1        loadedArray[29]
#define LOADED_P2_WALL_2        loadedArray[30]
#define LOADED_P2_WALL_3        loadedArray[31]
#define LOADED_P2_WALL_4        loadedArray[32]
#define LOADED_P2_WALL_5        loadedArray[33]
#define LOADED_P2_FLOOR         loadedArray[34]
#define LOADED_P2_MOSAIC        loadedArray[35]

#define LOADED_P3_WALL_1        loadedArray[36]
#define LOADED_P3_WALL_2        loadedArray[37]
#define LOADED_P3_WALL_3        loadedArray[38]
#define LOADED_P3_WALL_4        loadedArray[39]
#define LOADED_P3_WALL_5        loadedArray[40]
#define LOADED_P3_FLOOR         loadedArray[41]
#define LOADED_P3_MOSAIC        loadedArray[42]

#define LOADED_P4_WALL_1        loadedArray[43]
#define LOADED_P4_WALL_2        loadedArray[44]
#define LOADED_P4_WALL_3        loadedArray[45]
#define LOADED_P4_WALL_4        loadedArray[46]
#define LOADED_P4_WALL_5        loadedArray[47]
#define LOADED_P4_FLOOR         loadedArray[48]
#define LOADED_P4_MOSAIC        loadedArray[49]

#define LOADED_LID              loadedArray[50]
#define LOADED_TILE_BAG         loadedArray[51]
#define LOADED_TYPE             loadedArray[52]


#endif // COSC_ASS_TWO_TYPES
