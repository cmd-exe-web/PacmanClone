#pragma once

const int SCREEN_HEIGHT = 620;
const int SCREEN_WIDTH = 560;
const int targetFps = 144;

const int ROWS = SCREEN_WIDTH / 28;
const int COLS = SCREEN_WIDTH / 31;

const int TILE_SIZE = 20;

enum Direction {
	none, right, up, left, down
};

/*
	"############################"
	"#            ##            #"
	"# #### ##### ## ##### #### #"
	"# #  # #   # ## #   # #  # #"
	"# #### ##### ## ##### #### #"
	"#                          #"
	"# #### ## ######## ## #### #"
	"# #### ## ######## ## #### #"
	"#      ##    ##    ##      #"
	"###### ##### ## ##### ######"
	"     # ##### ## ##### #     "
	"     # ##          ## #     "
	"     # ## ######## ## #     "
	"###### ## #      # ## ######"
	"          #      #          "
	"###### ## #      # ## ######"
	"     # ## ######## ## #     "
	"     # ##          ## #     "
	"     # ## ######## ## #     "
	"###### ## ######## ## ######"
	"#            ##            #"
	"# #### ##### ## ##### #### #"
	"# #### ##### ## ##### #### #"
	"#   ##                ##   #"
	"### ## ## ######## ## ## ###"
	"### ## ## ######## ## ## ###"
	"#      ##    ##    ##      #"
	"# ########## ## ########## #"
	"# ########## ## ########## #"
	"#                          #"
	"############################"
*/
