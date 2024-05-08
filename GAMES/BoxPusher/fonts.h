//Total colors 3
const PROGMEM uint16_t bigfont_pal[] = {
10257,0,65535,
};

//Sprite sheet:16x4
const PROGMEM uint8_t bigfont [][130] ={
//[0] cell:0x0 
{
32,16, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[1] cell:1x0 
{
32,16, 0,21,0,0,0,0,0,0, 0,106,84,0,0,0,0,0, 0,106,169,0,0,0,0,0, 0,106,169,64,0,0,0,0, 0,106,165,64,0,0,0,0, 0,106,165,0,0,0,0,0, 0,106,149,0,0,0,0,0, 0,106,148,0,0,0,0,0, 0,106,84,0,0,0,0,0, 0,106,80,0,0,0,0,0, 0,21,80,0,0,0,0,0, 0,105,64,0,0,0,0,0, 1,170,64,0,0,0,0,0, 0,105,80,0,0,0,0,0, 0,21,64,0,0,0,0,0, 0,5,0,0,0,0,0,0, 
},
//[2] cell:2x0 
{
32,16, 21,85,0,0,0,0,0,0, 26,105,0,0,0,0,0,0, 18,73,0,0,0,0,0,0, 6,89,0,0,0,0,0,0, 1,69,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[3] cell:3x0 
{
32,16, 21,84,0,0,0,0,0,0, 89,101,0,0,0,0,0,0, 106,169,0,0,0,0,0,0, 89,101,0,0,0,0,0,0, 89,101,0,0,0,0,0,0, 106,169,0,0,0,0,0,0, 89,101,0,0,0,0,0,0, 21,84,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[4] cell:4x0 
{
32,16, 5,149,0,0,0,0,0,0, 18,169,0,0,0,0,0,0, 25,149,0,0,0,0,0,0, 18,161,0,0,0,0,0,0, 21,153,0,0,0,0,0,0, 26,161,0,0,0,0,0,0, 21,148,0,0,0,0,0,0, 1,80,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[5] cell:5x0 
{
32,16, 21,5,0,0,0,0,0,0, 72,89,0,0,0,0,0,0, 102,100,0,0,0,0,0,0, 72,148,0,0,0,0,0,0, 22,33,0,0,0,0,0,0, 25,153,0,0,0,0,0,0, 101,33,0,0,0,0,0,0, 80,84,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[6] cell:6x0 
{
32,16, 5,80,0,0,0,0,0,0, 18,132,0,0,0,0,0,0, 25,100,0,0,0,0,0,0, 90,84,0,0,0,0,0,0, 97,101,0,0,0,0,0,0, 101,41,0,0,0,0,0,0, 74,149,0,0,0,0,0,0, 21,80,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[7] cell:7x0 
{
32,16, 0,1,0,0,0,0,0,0, 0,6,64,0,0,0,0,0, 0,26,80,0,0,0,0,0, 0,106,144,0,0,0,0,0, 1,170,148,0,0,0,0,0, 6,170,84,0,0,0,0,0, 1,165,80,0,0,0,0,0, 0,85,64,0,0,0,0,0, 0,21,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[8] cell:8x0 
{
32,16, 1,80,0,0,0,0,0,0, 4,144,0,0,0,0,0,0, 6,16,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 6,16,0,0,0,0,0,0, 4,144,0,0,0,0,0,0, 1,80,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[9] cell:9x0 
{
32,16, 5,64,0,0,0,0,0,0, 6,16,0,0,0,0,0,0, 4,144,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 4,144,0,0,0,0,0,0, 6,16,0,0,0,0,0,0, 5,64,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[10] cell:10x0 
{
32,16, 20,5,0,0,0,0,0,0, 25,25,0,0,0,0,0,0, 6,100,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 6,100,0,0,0,0,0,0, 25,25,0,0,0,0,0,0, 20,5,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[11] cell:11x0 
{
32,16, 1,80,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 21,149,0,0,0,0,0,0, 26,169,0,0,0,0,0,0, 21,149,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 1,80,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[12] cell:12x0 
{
32,16, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,16,0,0,0,0,0, 0,1,100,0,0,0,0,0, 0,6,169,0,0,0,0,0, 0,26,165,64,0,0,0,0, 0,106,165,0,0,0,0,0, 0,22,149,0,0,0,0,0, 0,5,84,0,0,0,0,0, 0,0,80,0,0,0,0,0, 
},
//[13] cell:13x0 
{
32,16, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,1,85,80,0,0,0,0, 5,86,170,164,0,0,0,0, 26,170,170,85,0,0,0,0, 26,170,165,84,0,0,0,0, 6,170,85,64,0,0,0,0, 6,165,84,0,0,0,0,0, 6,85,64,0,0,0,0,0, 1,84,0,0,0,0,0,0, 0,64,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[14] cell:14x0 
{
32,16, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,5,0,0,0,0,0,0, 0,26,64,0,0,0,0,0, 0,106,144,0,0,0,0,0, 0,26,84,0,0,0,0,0, 0,5,80,0,0,0,0,0, 0,1,64,0,0,0,0,0, 
},
//[15] cell:15x0 
{
32,16, 0,5,0,0,0,0,0,0, 0,25,0,0,0,0,0,0, 0,100,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 25,0,0,0,0,0,0,0, 100,0,0,0,0,0,0,0, 80,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[16] cell:0x1 
{
32,16, 0,0,0,0,0,0,0,0, 0,5,84,0,0,0,0,0, 0,26,169,64,0,0,0,0, 0,105,106,144,0,0,0,0, 1,165,90,164,0,0,0,0, 6,165,26,165,0,0,0,0, 26,149,6,165,0,0,0,0, 26,148,6,165,0,0,0,0, 106,148,6,149,0,0,0,0, 106,148,6,148,0,0,0,0, 106,164,26,84,0,0,0,0, 26,169,105,80,0,0,0,0, 6,170,165,64,0,0,0,0, 1,170,85,0,0,0,0,0, 0,85,84,0,0,0,0,0, 0,21,64,0,0,0,0,0, 
},
//[17] cell:1x1 
{
32,16, 0,1,64,0,0,0,0,0, 0,22,144,0,0,0,0,0, 1,106,148,0,0,0,0,0, 6,170,148,0,0,0,0,0, 1,166,164,0,0,0,0,0, 1,150,165,0,0,0,0,0, 0,86,165,0,0,0,0,0, 0,26,165,0,0,0,0,0, 0,26,169,0,0,0,0,0, 0,26,169,64,0,0,0,0, 0,26,169,64,0,0,0,0, 0,106,170,64,0,0,0,0, 0,106,170,80,0,0,0,0, 0,106,85,80,0,0,0,0, 0,21,85,64,0,0,0,0, 0,5,64,0,0,0,0,0, 
},
//[18] cell:2x1 
{
32,16, 0,21,80,0,0,0,0,0, 1,106,165,0,0,0,0,0, 6,169,170,64,0,0,0,0, 26,165,106,144,0,0,0,0, 106,149,106,148,0,0,0,0, 26,84,106,148,0,0,0,0, 6,81,170,84,0,0,0,0, 1,86,165,80,0,0,0,0, 0,90,149,64,0,0,0,0, 0,105,85,64,0,0,0,0, 21,170,170,144,0,0,0,0, 106,170,170,148,0,0,0,0, 22,170,170,164,0,0,0,0, 5,149,86,165,0,0,0,0, 0,85,85,85,0,0,0,0, 0,16,0,84,0,0,0,0, 
},
//[19] cell:3x1 
{
32,16, 1,85,64,0,0,0,0,0, 22,170,148,0,0,0,0,0, 106,166,169,0,0,0,0,0, 26,149,170,64,0,0,0,0, 6,84,106,144,0,0,0,0, 1,85,106,148,0,0,0,0, 0,90,170,84,0,0,0,0, 0,6,165,80,0,0,0,0, 1,65,170,64,0,0,0,0, 22,144,106,144,0,0,0,0, 106,148,26,164,0,0,0,0, 26,164,26,165,0,0,0,0, 6,169,90,149,0,0,0,0, 1,170,169,84,0,0,0,0, 0,85,85,80,0,0,0,0, 0,21,85,0,0,0,0,0, 
},
//[20] cell:4x1 
{
32,16, 0,5,64,0,0,0,0,0, 0,90,144,0,0,0,0,0, 1,170,148,0,0,0,0,0, 1,170,84,0,0,0,0,0, 1,170,80,0,0,0,0,0, 6,169,80,0,0,0,0,0, 6,169,100,0,0,0,0,0, 6,165,165,0,0,0,0,0, 6,165,165,64,0,0,0,0, 26,149,166,144,0,0,0,0, 26,154,170,148,0,0,0,0, 26,170,170,164,0,0,0,0, 106,170,170,165,0,0,0,0, 21,86,165,85,0,0,0,0, 5,85,85,84,0,0,0,0, 0,0,84,0,0,0,0,0, 
},
//[21] cell:5x1 
{
32,16, 0,0,5,80,0,0,0,0, 0,5,90,164,0,0,0,0, 5,90,170,165,0,0,0,0, 26,170,170,149,0,0,0,0, 26,170,170,148,0,0,0,0, 26,165,85,84,0,0,0,0, 26,149,85,80,0,0,0,0, 26,170,165,0,0,0,0,0, 5,90,170,64,0,0,0,0, 22,149,170,144,0,0,0,0, 106,149,106,148,0,0,0,0, 106,164,26,148,0,0,0,0, 26,169,106,84,0,0,0,0, 5,170,169,80,0,0,0,0, 1,85,85,64,0,0,0,0, 0,21,85,0,0,0,0,0, 
},
//[22] cell:6x1 
{
32,16, 0,0,64,0,0,0,0,0, 0,5,144,0,0,0,0,0, 0,90,164,0,0,0,0,0, 1,170,169,0,0,0,0,0, 6,170,170,64,0,0,0,0, 26,170,149,80,0,0,0,0, 26,169,85,64,0,0,0,0, 106,170,165,0,0,0,0,0, 106,150,170,64,0,0,0,0, 106,85,170,144,0,0,0,0, 105,81,170,148,0,0,0,0, 105,65,170,148,0,0,0,0, 26,86,170,84,0,0,0,0, 6,170,169,80,0,0,0,0, 1,85,85,64,0,0,0,0, 0,85,85,0,0,0,0,0, 
},
//[23] cell:7x1 
{
32,16, 5,0,0,0,0,0,0,0, 26,85,0,80,0,0,0,0, 26,170,85,164,0,0,0,0, 26,170,170,165,0,0,0,0, 106,170,170,165,0,0,0,0, 106,149,86,165,0,0,0,0, 21,85,90,149,0,0,0,0, 5,80,26,148,0,0,0,0, 0,0,106,148,0,0,0,0, 0,1,170,148,0,0,0,0, 0,1,170,84,0,0,0,0, 0,6,170,80,0,0,0,0, 0,26,170,80,0,0,0,0, 0,5,106,80,0,0,0,0, 0,1,85,80,0,0,0,0, 0,0,5,64,0,0,0,0, 
},
//[24] cell:8x1 
{
32,16, 0,0,0,0,0,0,0,0, 0,21,80,0,0,0,0,0, 1,106,164,0,0,0,0,0, 6,166,169,0,0,0,0,0, 26,85,170,64,0,0,0,0, 106,148,106,80,0,0,0,0, 106,165,106,80,0,0,0,0, 26,170,169,80,0,0,0,0, 6,170,170,144,0,0,0,0, 26,149,170,164,0,0,0,0, 106,149,106,165,0,0,0,0, 106,148,106,165,0,0,0,0, 26,165,170,149,0,0,0,0, 6,170,170,84,0,0,0,0, 1,85,85,80,0,0,0,0, 0,85,85,64,0,0,0,0, 
},
//[25] cell:9x1 
{
32,16, 1,85,80,0,0,0,0,0, 6,170,165,0,0,0,0,0, 26,165,170,64,0,0,0,0, 106,149,106,144,0,0,0,0, 106,84,106,164,0,0,0,0, 26,80,106,165,0,0,0,0, 6,149,170,149,0,0,0,0, 1,170,170,148,0,0,0,0, 0,86,170,84,0,0,0,0, 0,26,170,80,0,0,0,0, 0,106,169,80,0,0,0,0, 1,170,169,64,0,0,0,0, 0,90,165,64,0,0,0,0, 0,21,165,0,0,0,0,0, 0,1,85,0,0,0,0,0, 0,0,20,0,0,0,0,0, 
},
//[26] cell:10x1 
{
32,16, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,5,0,0,0,0,0,0, 0,26,64,0,0,0,0,0, 0,106,144,0,0,0,0,0, 0,26,84,0,0,0,0,0, 0,5,80,0,0,0,0,0, 0,1,64,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,5,0,0,0,0,0,0, 0,26,64,0,0,0,0,0, 0,106,144,0,0,0,0,0, 0,26,84,0,0,0,0,0, 0,5,80,0,0,0,0,0, 0,1,64,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[27] cell:11x1 
{
32,16, 5,80,0,0,0,0,0,0, 6,144,0,0,0,0,0,0, 6,144,0,0,0,0,0,0, 5,80,0,0,0,0,0,0, 6,144,0,0,0,0,0,0, 4,144,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 0,80,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[28] cell:12x1 
{
32,16, 0,100,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 25,0,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 0,100,0,0,0,0,0,0, 0,20,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[29] cell:13x1 
{
32,16, 0,0,0,0,0,0,0,0, 21,85,0,0,0,0,0,0, 26,169,0,0,0,0,0,0, 21,85,0,0,0,0,0,0, 26,169,0,0,0,0,0,0, 21,85,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[30] cell:14x1 
{
32,16, 25,0,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 0,100,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 25,0,0,0,0,0,0,0, 20,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[31] cell:15x1 
{
32,16, 0,85,84,0,0,0,0,0, 5,170,169,64,0,0,0,0, 26,169,170,144,0,0,0,0, 106,165,106,164,0,0,0,0, 26,149,106,165,0,0,0,0, 6,84,106,165,0,0,0,0, 1,85,170,149,0,0,0,0, 0,90,165,84,0,0,0,0, 1,170,85,80,0,0,0,0, 0,101,84,0,0,0,0,0, 0,21,64,0,0,0,0,0, 0,105,0,0,0,0,0,0, 1,170,64,0,0,0,0,0, 0,105,80,0,0,0,0,0, 0,21,64,0,0,0,0,0, 0,5,0,0,0,0,0,0, 
},
//[32] cell:0x2 
{
32,16, 26,132,0,0,0,0,0,0, 101,97,0,0,0,0,0,0, 146,153,0,0,0,0,0,0, 153,89,0,0,0,0,0,0, 146,153,0,0,0,0,0,0, 37,97,0,0,0,0,0,0, 74,133,0,0,0,0,0,0, 21,84,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[33] cell:1x2 
{
32,16, 0,4,0,0,0,0,0,0, 0,25,0,0,0,0,0,0, 0,106,64,0,0,0,0,0, 0,106,144,0,0,0,0,0, 1,166,164,0,0,0,0,0, 1,165,169,0,0,0,0,0, 6,165,106,64,0,0,0,0, 6,165,170,144,0,0,0,0, 26,170,170,164,0,0,0,0, 26,170,90,165,0,0,0,0, 106,165,86,165,0,0,0,0, 106,165,70,149,0,0,0,0, 26,165,1,148,0,0,0,0, 5,165,0,84,0,0,0,0, 1,85,0,16,0,0,0,0, 0,20,0,0,0,0,0,0, 
},
//[34] cell:2x2 
{
32,16, 0,20,0,0,0,0,0,0, 5,105,84,0,0,0,0,0, 26,170,169,0,0,0,0,0, 26,170,170,64,0,0,0,0, 5,169,106,144,0,0,0,0, 1,169,90,148,0,0,0,0, 1,169,106,84,0,0,0,0, 1,170,170,80,0,0,0,0, 6,169,90,144,0,0,0,0, 6,169,86,164,0,0,0,0, 22,169,70,165,0,0,0,0, 106,169,90,165,0,0,0,0, 106,170,170,149,0,0,0,0, 21,106,170,84,0,0,0,0, 5,85,85,80,0,0,0,0, 0,5,85,64,0,0,0,0, 
},
//[35] cell:3x2 
{
32,16, 0,0,0,0,0,0,0,0, 0,5,84,0,0,0,0,0, 0,90,169,0,0,0,0,0, 1,170,170,64,0,0,0,0, 6,165,170,144,0,0,0,0, 26,149,106,84,0,0,0,0, 26,148,25,80,0,0,0,0, 106,148,5,64,0,0,0,0, 106,148,1,80,0,0,0,0, 106,148,6,164,0,0,0,0, 26,165,90,165,0,0,0,0, 6,170,170,149,0,0,0,0, 1,106,169,84,0,0,0,0, 0,85,85,80,0,0,0,0, 0,5,85,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[36] cell:4x2 
{
32,16, 0,0,0,0,0,0,0,0, 5,85,64,0,0,0,0,0, 26,170,148,0,0,0,0,0, 26,170,169,0,0,0,0,0, 106,170,170,64,0,0,0,0, 106,170,170,144,0,0,0,0, 21,169,90,164,0,0,0,0, 5,169,86,165,0,0,0,0, 1,169,65,165,0,0,0,0, 1,169,65,165,0,0,0,0, 5,169,65,165,0,0,0,0, 26,169,86,165,0,0,0,0, 26,170,170,149,0,0,0,0, 26,170,170,84,0,0,0,0, 5,85,85,80,0,0,0,0, 1,85,85,64,0,0,0,0, 
},
//[37] cell:5x2 
{
32,16, 1,85,64,0,0,0,0,0, 6,170,149,80,0,0,0,0, 6,170,170,164,0,0,0,0, 1,170,170,165,0,0,0,0, 1,169,85,85,0,0,0,0, 1,169,105,84,0,0,0,0, 1,169,169,64,0,0,0,0, 1,170,170,64,0,0,0,0, 1,170,170,80,0,0,0,0, 1,170,85,80,0,0,0,0, 1,170,85,80,0,0,0,0, 5,170,90,164,0,0,0,0, 26,170,170,165,0,0,0,0, 26,170,170,165,0,0,0,0, 5,85,85,85,0,0,0,0, 1,85,85,84,0,0,0,0, 
},
//[38] cell:6x2 
{
32,16, 0,0,5,0,0,0,0,0, 5,1,90,64,0,0,0,0, 26,86,170,80,0,0,0,0, 26,170,170,80,0,0,0,0, 106,170,170,144,0,0,0,0, 106,170,170,148,0,0,0,0, 22,165,85,84,0,0,0,0, 6,165,85,80,0,0,0,0, 6,170,164,0,0,0,0,0, 6,166,165,0,0,0,0,0, 26,165,101,0,0,0,0,0, 26,169,85,0,0,0,0,0, 26,169,68,0,0,0,0,0, 5,169,64,0,0,0,0,0, 1,85,64,0,0,0,0,0, 0,21,0,0,0,0,0,0, 
},
//[39] cell:7x2 
{
32,16, 0,0,4,0,0,0,0,0, 0,0,89,0,0,0,0,0, 0,5,170,64,0,0,0,0, 0,26,170,144,0,0,0,0, 1,106,170,164,0,0,0,0, 6,169,85,85,0,0,0,0, 26,149,85,84,0,0,0,0, 26,85,105,0,0,0,0,0, 106,80,106,64,0,0,0,0, 106,144,106,80,0,0,0,0, 106,165,170,144,0,0,0,0, 26,170,170,148,0,0,0,0, 6,169,106,148,0,0,0,0, 1,85,105,84,0,0,0,0, 0,85,21,80,0,0,0,0, 0,0,5,0,0,0,0,0, 
},
//[40] cell:8x2 
{
32,16, 0,80,21,0,0,0,0,0, 1,164,106,64,0,0,0,0, 1,165,106,80,0,0,0,0, 1,165,106,80,0,0,0,0, 6,165,106,80,0,0,0,0, 6,170,90,144,0,0,0,0, 6,170,170,148,0,0,0,0, 26,169,106,148,0,0,0,0, 26,165,86,164,0,0,0,0, 26,165,6,165,0,0,0,0, 106,165,6,165,0,0,0,0, 106,165,1,165,0,0,0,0, 106,85,1,165,0,0,0,0, 21,84,1,149,0,0,0,0, 5,64,0,84,0,0,0,0, 0,0,0,16,0,0,0,0, 
},
//[41] cell:9x2 
{
32,16, 0,5,85,0,0,0,0,0, 5,90,170,64,0,0,0,0, 26,170,170,80,0,0,0,0, 26,170,149,80,0,0,0,0, 26,150,149,64,0,0,0,0, 5,86,148,0,0,0,0,0, 1,86,148,0,0,0,0,0, 0,26,148,0,0,0,0,0, 0,26,164,0,0,0,0,0, 0,26,165,0,0,0,0,0, 1,90,165,64,0,0,0,0, 6,170,170,144,0,0,0,0, 1,90,170,148,0,0,0,0, 0,85,106,148,0,0,0,0, 0,1,85,84,0,0,0,0, 0,0,5,80,0,0,0,0, 
},
//[42] cell:10x2 
{
32,16, 0,0,5,80,0,0,0,0, 0,5,90,164,0,0,0,0, 5,90,170,165,0,0,0,0, 26,170,170,85,0,0,0,0, 6,165,170,84,0,0,0,0, 1,85,170,80,0,0,0,0, 0,84,106,80,0,0,0,0, 1,144,106,80,0,0,0,0, 6,164,26,80,0,0,0,0, 26,169,26,80,0,0,0,0, 26,170,90,80,0,0,0,0, 6,170,170,80,0,0,0,0, 1,106,169,80,0,0,0,0, 0,86,165,64,0,0,0,0, 0,5,85,0,0,0,0,0, 0,0,84,0,0,0,0,0, 
},
//[43] cell:11x2 
{
32,16, 0,80,1,0,0,0,0,0, 1,164,6,64,0,0,0,0, 1,165,26,144,0,0,0,0, 1,165,106,164,0,0,0,0, 1,165,170,165,0,0,0,0, 6,166,170,85,0,0,0,0, 6,170,165,84,0,0,0,0, 6,170,85,64,0,0,0,0, 6,170,165,0,0,0,0,0, 26,166,170,80,0,0,0,0, 26,165,170,164,0,0,0,0, 26,165,106,165,0,0,0,0, 26,165,26,149,0,0,0,0, 5,165,6,84,0,0,0,0, 1,85,1,80,0,0,0,0, 0,20,0,64,0,0,0,0, 
},
//[44] cell:12x2 
{
32,16, 0,0,0,0,0,0,0,0, 5,84,0,0,0,0,0,0, 26,169,0,0,0,0,0,0, 26,169,64,0,0,0,0,0, 26,169,64,0,0,0,0,0, 26,165,64,0,0,0,0,0, 26,165,0,0,0,0,0,0, 26,165,0,0,0,0,0,0, 26,149,5,64,0,0,0,0, 26,149,90,144,0,0,0,0, 26,150,170,148,0,0,0,0, 26,170,170,164,0,0,0,0, 26,170,170,165,0,0,0,0, 26,170,85,85,0,0,0,0, 5,85,85,84,0,0,0,0, 1,85,64,0,0,0,0,0, 
},
//[45] cell:13x2 
{
32,16, 0,0,0,80,0,0,0,0, 0,64,1,164,0,0,0,0, 1,144,6,165,0,0,0,0, 6,164,26,149,0,0,0,0, 6,169,106,148,0,0,0,0, 6,170,170,148,0,0,0,0, 6,154,166,148,0,0,0,0, 6,150,150,148,0,0,0,0, 26,149,90,148,0,0,0,0, 26,148,90,164,0,0,0,0, 26,148,26,165,0,0,0,0, 106,148,26,165,0,0,0,0, 106,148,26,165,0,0,0,0, 22,148,26,85,0,0,0,0, 5,84,5,84,0,0,0,0, 0,80,1,64,0,0,0,0, 
},
//[46] cell:14x2 
{
32,16, 1,64,0,0,0,0,0,0, 22,144,5,0,0,0,0,0, 106,148,26,80,0,0,0,0, 106,148,26,164,0,0,0,0, 26,148,26,165,0,0,0,0, 26,164,26,165,0,0,0,0, 26,169,26,149,0,0,0,0, 26,170,90,148,0,0,0,0, 26,154,170,148,0,0,0,0, 106,150,170,148,0,0,0,0, 106,149,170,84,0,0,0,0, 106,148,106,80,0,0,0,0, 106,148,26,80,0,0,0,0, 22,148,6,80,0,0,0,0, 5,84,1,80,0,0,0,0, 0,80,0,64,0,0,0,0, 
},
//[47] cell:15x2 
{
32,16, 0,0,0,0,0,0,0,0, 0,5,80,0,0,0,0,0, 0,90,165,0,0,0,0,0, 1,170,170,64,0,0,0,0, 6,149,170,144,0,0,0,0, 26,85,106,148,0,0,0,0, 106,80,26,164,0,0,0,0, 106,80,26,165,0,0,0,0, 106,144,6,165,0,0,0,0, 106,165,6,165,0,0,0,0, 26,170,90,149,0,0,0,0, 6,170,170,84,0,0,0,0, 1,106,149,80,0,0,0,0, 0,85,85,64,0,0,0,0, 0,5,80,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[48] cell:0x3 
{
32,16, 5,85,64,0,0,0,0,0, 26,170,149,0,0,0,0,0, 26,170,170,64,0,0,0,0, 106,170,170,144,0,0,0,0, 106,170,170,164,0,0,0,0, 22,165,90,165,0,0,0,0, 6,165,86,165,0,0,0,0, 6,165,90,149,0,0,0,0, 6,170,170,84,0,0,0,0, 26,170,165,80,0,0,0,0, 26,165,85,64,0,0,0,0, 26,165,84,0,0,0,0,0, 26,165,0,0,0,0,0,0, 26,149,0,0,0,0,0,0, 5,84,0,0,0,0,0,0, 1,80,0,0,0,0,0,0, 
},
//[49] cell:1x3 
{
32,16, 0,5,80,0,0,0,0,0, 1,90,165,0,0,0,0,0, 6,170,170,64,0,0,0,0, 26,150,170,144,0,0,0,0, 106,85,106,164,0,0,0,0, 106,80,90,165,0,0,0,0, 106,80,70,165,0,0,0,0, 106,145,150,165,0,0,0,0, 26,150,166,149,0,0,0,0, 26,165,170,84,0,0,0,0, 6,169,106,144,0,0,0,0, 1,106,170,164,0,0,0,0, 0,85,90,149,0,0,0,0, 0,5,86,84,0,0,0,0, 0,0,1,80,0,0,0,0, 0,0,0,64,0,0,0,0, 
},
//[50] cell:2x3 
{
32,16, 0,21,80,0,0,0,0,0, 21,106,164,0,0,0,0,0, 106,170,169,0,0,0,0,0, 106,170,170,64,0,0,0,0, 106,165,90,80,0,0,0,0, 26,85,106,80,0,0,0,0, 26,85,169,80,0,0,0,0, 26,170,149,64,0,0,0,0, 26,154,165,0,0,0,0,0, 26,150,170,80,0,0,0,0, 26,165,170,164,0,0,0,0, 26,165,106,165,0,0,0,0, 26,165,26,149,0,0,0,0, 26,85,6,84,0,0,0,0, 5,84,1,80,0,0,0,0, 1,64,0,64,0,0,0,0, 
},
//[51] cell:3x3 
{
32,16, 0,0,5,0,0,0,0,0, 0,0,90,64,0,0,0,0, 0,5,170,80,0,0,0,0, 0,90,170,144,0,0,0,0, 1,170,170,148,0,0,0,0, 6,165,85,84,0,0,0,0, 6,169,85,80,0,0,0,0, 1,170,169,64,0,0,0,0, 0,85,106,144,0,0,0,0, 1,85,90,164,0,0,0,0, 6,170,170,165,0,0,0,0, 6,170,170,149,0,0,0,0, 26,170,170,84,0,0,0,0, 26,169,85,80,0,0,0,0, 5,85,85,64,0,0,0,0, 1,85,0,0,0,0,0,0, 
},
//[52] cell:4x3 
{
32,16, 0,0,1,80,0,0,0,0, 0,1,86,164,0,0,0,0, 0,86,170,165,0,0,0,0, 21,170,170,149,0,0,0,0, 106,170,170,148,0,0,0,0, 21,90,170,148,0,0,0,0, 5,90,149,84,0,0,0,0, 0,106,149,80,0,0,0,0, 0,106,148,0,0,0,0,0, 1,170,148,0,0,0,0,0, 1,170,164,0,0,0,0,0, 6,170,165,0,0,0,0,0, 6,170,165,0,0,0,0,0, 1,90,165,0,0,0,0,0, 0,85,85,0,0,0,0,0, 0,1,84,0,0,0,0,0, 
},
//[53] cell:5x3 
{
32,16, 0,0,0,0,0,0,0,0, 0,0,0,80,0,0,0,0, 0,0,5,164,0,0,0,0, 20,0,90,165,0,0,0,0, 105,65,170,165,0,0,0,0, 106,144,106,165,0,0,0,0, 106,148,106,149,0,0,0,0, 106,148,26,148,0,0,0,0, 106,148,26,148,0,0,0,0, 106,148,26,148,0,0,0,0, 26,164,26,84,0,0,0,0, 26,165,26,80,0,0,0,0, 6,169,105,80,0,0,0,0, 1,170,165,64,0,0,0,0, 0,85,85,0,0,0,0,0, 0,21,84,0,0,0,0,0, 
},
//[54] cell:6x3 
{
32,16, 0,0,1,80,0,0,0,0, 1,64,22,164,0,0,0,0, 22,144,106,165,0,0,0,0, 106,148,106,149,0,0,0,0, 26,148,106,148,0,0,0,0, 6,165,170,84,0,0,0,0, 1,165,170,80,0,0,0,0, 1,169,169,80,0,0,0,0, 0,105,169,64,0,0,0,0, 0,26,165,64,0,0,0,0, 0,6,165,0,0,0,0,0, 0,6,149,0,0,0,0,0, 0,1,148,0,0,0,0,0, 0,0,84,0,0,0,0,0, 0,0,16,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[55] cell:7x3 
{
32,16, 1,64,5,0,0,0,0,0, 22,144,26,80,0,0,0,0, 106,148,26,164,0,0,0,0, 106,148,26,165,0,0,0,0, 106,148,26,149,0,0,0,0, 106,148,26,148,0,0,0,0, 26,149,26,148,0,0,0,0, 26,90,90,84,0,0,0,0, 26,106,154,80,0,0,0,0, 26,170,170,80,0,0,0,0, 26,165,170,80,0,0,0,0, 26,149,106,80,0,0,0,0, 106,84,25,80,0,0,0,0, 105,80,5,64,0,0,0,0, 21,64,1,0,0,0,0,0, 5,0,0,0,0,0,0,0, 
},
//[56] cell:8x3 
{
32,16, 0,64,0,64,0,0,0,0, 1,144,1,144,0,0,0,0, 6,164,6,148,0,0,0,0, 26,165,26,84,0,0,0,0, 106,169,106,80,0,0,0,0, 26,170,169,80,0,0,0,0, 5,170,169,64,0,0,0,0, 1,106,165,64,0,0,0,0, 0,106,169,0,0,0,0,0, 1,170,170,64,0,0,0,0, 6,170,90,144,0,0,0,0, 26,170,86,164,0,0,0,0, 6,169,81,149,0,0,0,0, 1,105,64,84,0,0,0,0, 0,85,64,16,0,0,0,0, 0,5,0,0,0,0,0,0, 
},
//[57] cell:9x3 
{
32,16, 0,0,0,64,0,0,0,0, 0,20,1,144,0,0,0,0, 0,105,1,164,0,0,0,0, 1,169,70,165,0,0,0,0, 6,169,70,149,0,0,0,0, 26,170,90,148,0,0,0,0, 5,170,90,148,0,0,0,0, 1,90,170,84,0,0,0,0, 0,21,170,80,0,0,0,0, 0,6,170,80,0,0,0,0, 0,26,169,80,0,0,0,0, 0,106,169,64,0,0,0,0, 1,170,169,64,0,0,0,0, 6,170,85,64,0,0,0,0, 1,85,85,0,0,0,0,0, 0,85,64,0,0,0,0,0, 
},
//[58] cell:10x3 
{
32,16, 5,64,0,0,0,0,0,0, 26,149,64,0,0,0,0,0, 26,170,149,64,0,0,0,0, 106,170,170,144,0,0,0,0, 106,170,170,84,0,0,0,0, 106,149,169,80,0,0,0,0, 21,86,165,64,0,0,0,0, 5,90,149,64,0,0,0,0, 0,106,86,144,0,0,0,0, 1,169,106,148,0,0,0,0, 22,166,170,148,0,0,0,0, 106,170,170,148,0,0,0,0, 106,170,170,164,0,0,0,0, 25,85,90,165,0,0,0,0, 5,85,85,85,0,0,0,0, 1,0,1,84,0,0,0,0, 
},
//[59] cell:11x3 
{
32,16, 5,80,0,0,0,0,0,0, 6,144,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 6,144,0,0,0,0,0,0, 5,80,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[60] cell:12x3 
{
32,16, 80,0,0,0,0,0,0,0, 100,0,0,0,0,0,0,0, 25,0,0,0,0,0,0,0, 6,64,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 0,100,0,0,0,0,0,0, 0,25,0,0,0,0,0,0, 0,5,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[61] cell:13x3 
{
32,16, 5,80,0,0,0,0,0,0, 6,144,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 6,144,0,0,0,0,0,0, 5,80,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[62] cell:14x3 
{
32,16, 0,64,0,0,0,0,0,0, 1,144,0,0,0,0,0,0, 6,100,0,0,0,0,0,0, 25,25,0,0,0,0,0,0, 20,5,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
//[63] cell:15x3 
{
32,16, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 85,85,0,0,0,0,0,0, 106,169,0,0,0,0,0,0, 85,85,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
},
};



//Total colors 4
const PROGMEM uint16_t guiFont_pal[] = {
63519,0,65535,25357,
};

//Sprite sheet:16x8
const PROGMEM uint8_t guiFont [][34] ={
//[0] cell:0x0 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[1] cell:1x0 
{
8,8, 17,17,17,17, 19,34,34,34, 18,35,17,17, 18,49,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 
},
//[2] cell:2x0 
{
8,8, 17,17,17,17, 34,34,34,34, 17,17,17,17, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[3] cell:3x0 
{
8,8, 17,17,17,17, 34,34,34,49, 17,17,50,33, 0,0,19,33, 0,0,1,33, 0,0,1,33, 0,0,1,33, 0,0,1,33, 
},
//[4] cell:4x0 
{
8,8, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,49,0,0, 18,35,17,17, 19,34,34,34, 17,17,17,17, 
},
//[5] cell:5x0 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 17,17,17,17, 34,34,34,34, 17,17,17,17, 
},
//[6] cell:6x0 
{
8,8, 0,0,1,33, 0,0,1,33, 0,0,1,33, 0,0,1,33, 0,0,19,33, 17,17,50,33, 34,34,34,49, 17,17,17,17, 
},
//[7] cell:7x0 
{
8,8, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 
},
//[8] cell:8x0 
{
8,8, 0,0,1,33, 0,0,1,33, 0,0,1,33, 0,0,1,33, 0,0,1,33, 0,0,1,33, 0,0,1,33, 0,0,1,33, 
},
//[9] cell:9x0 
{
8,8, 18,16,0,0, 18,16,0,0, 18,49,0,0, 18,35,17,17, 18,34,34,34, 18,35,17,17, 18,49,0,0, 18,16,0,0, 
},
//[10] cell:10x0 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 17,17,17,17, 34,34,34,34, 17,17,17,17, 0,0,0,0, 0,0,0,0, 
},
//[11] cell:11x0 
{
8,8, 0,0,1,33, 0,0,1,33, 0,0,19,33, 17,17,50,33, 34,34,34,33, 17,17,50,33, 0,0,19,33, 0,0,1,33, 
},
//[12] cell:12x0 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[13] cell:13x0 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[14] cell:14x0 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[15] cell:15x0 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[16] cell:0x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[17] cell:1x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[18] cell:2x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[19] cell:3x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[20] cell:4x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[21] cell:5x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[22] cell:6x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[23] cell:7x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[24] cell:8x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[25] cell:9x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[26] cell:10x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[27] cell:11x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[28] cell:12x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[29] cell:13x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[30] cell:14x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[31] cell:15x1 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[32] cell:0x2 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[33] cell:1x2 
{
8,8, 0,1,17,0, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,1,17,0, 0,1,33,0, 0,1,17,0, 
},
//[34] cell:2x2 
{
8,8, 1,17,17,17, 1,34,18,33, 1,50,19,33, 0,18,17,33, 0,1,16,17, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[35] cell:3x2 
{
8,8, 1,17,17,16, 17,33,18,17, 18,34,34,33, 17,33,18,17, 17,33,18,17, 18,34,34,33, 17,33,18,17, 1,17,17,16, 
},
//[36] cell:4x2 
{
8,8, 0,17,33,17, 1,50,34,33, 1,33,33,17, 1,50,34,49, 1,17,33,33, 1,34,34,49, 1,17,33,16, 0,1,17,0, 
},
//[37] cell:5x2 
{
8,8, 1,17,0,17, 19,35,17,33, 18,18,18,16, 19,35,33,16, 1,18,50,49, 1,33,33,33, 18,17,50,49, 17,0,17,16, 
},
//[38] cell:6x2 
{
8,8, 0,17,17,0, 1,50,35,16, 1,33,18,16, 17,34,17,16, 18,49,18,17, 18,17,50,33, 19,34,33,17, 1,17,17,0, 
},
//[39] cell:7x2 
{
8,8, 0,17,17,0, 0,18,33,0, 0,19,33,0, 0,1,33,0, 0,0,17,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[40] cell:8x2 
{
8,8, 0,1,17,0, 0,19,33,0, 0,18,49,0, 0,18,16,0, 0,18,16,0, 0,18,49,0, 0,19,33,0, 0,1,17,0, 
},
//[41] cell:9x2 
{
8,8, 0,17,16,0, 0,18,49,0, 0,19,33,0, 0,1,33,0, 0,1,33,0, 0,19,33,0, 0,18,49,0, 0,17,16,0, 
},
//[42] cell:10x2 
{
8,8, 1,16,0,17, 1,33,1,33, 0,18,18,16, 0,1,33,0, 0,18,18,16, 1,33,1,33, 1,16,0,17, 0,0,0,0, 
},
//[43] cell:11x2 
{
8,8, 0,1,17,0, 0,1,33,0, 1,17,33,17, 1,34,34,33, 1,17,33,17, 0,1,33,0, 0,1,17,0, 0,0,0,0, 
},
//[44] cell:12x2 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,17,17,0, 0,18,33,0, 0,19,33,0, 0,1,33,0, 0,0,17,0, 
},
//[45] cell:13x2 
{
8,8, 0,0,0,0, 0,0,0,0, 1,17,17,17, 1,34,34,33, 1,17,17,17, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[46] cell:14x2 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,1,17,0, 0,1,33,0, 0,1,17,0, 0,0,0,0, 
},
//[47] cell:15x2 
{
8,8, 0,0,0,17, 0,0,1,33, 0,0,18,16, 0,1,33,0, 0,18,16,0, 1,33,0,0, 18,16,0,0, 17,0,0,0, 
},
//[48] cell:0x3 
{
8,8, 1,17,17,16, 19,34,34,49, 18,49,50,33, 18,16,18,33, 18,16,18,33, 18,49,50,33, 19,34,34,49, 1,17,17,16, 
},
//[49] cell:1x3 
{
8,8, 1,17,17,0, 1,34,33,0, 1,18,33,0, 0,18,33,0, 0,18,33,0, 0,18,33,0, 0,18,33,0, 0,17,17,0, 
},
//[50] cell:2x3 
{
8,8, 17,17,17,16, 18,34,34,49, 17,17,18,33, 19,34,34,49, 18,35,17,16, 18,33,17,17, 18,34,34,33, 17,17,17,17, 
},
//[51] cell:3x3 
{
8,8, 17,17,17,0, 18,34,35,16, 17,17,34,16, 18,34,34,49, 17,17,50,33, 17,17,50,33, 18,34,34,49, 17,17,17,16, 
},
//[52] cell:4x3 
{
8,8, 17,17,17,16, 18,17,34,16, 18,17,34,16, 18,17,34,16, 18,17,34,17, 18,34,34,33, 17,17,34,17, 0,1,17,16, 
},
//[53] cell:5x3 
{
8,8, 17,17,17,16, 18,34,34,16, 18,17,17,16, 18,34,34,49, 17,17,50,33, 17,17,50,33, 18,34,34,49, 17,17,17,16, 
},
//[54] cell:6x3 
{
8,8, 1,17,17,16, 19,34,34,16, 18,17,17,16, 18,34,34,49, 18,17,50,33, 18,17,50,33, 19,34,34,49, 1,17,17,16, 
},
//[55] cell:7x3 
{
8,8, 17,17,17,17, 18,34,34,33, 17,17,18,33, 0,0,18,33, 0,0,18,33, 0,0,18,33, 0,0,18,33, 0,0,17,17, 
},
//[56] cell:8x3 
{
8,8, 1,17,17,16, 19,34,34,49, 18,17,50,33, 19,34,34,49, 18,17,50,33, 18,17,50,33, 19,34,34,49, 1,17,17,16, 
},
//[57] cell:9x3 
{
8,8, 1,17,17,16, 19,34,34,49, 18,17,50,33, 18,17,50,33, 19,34,34,33, 1,17,18,33, 1,34,34,49, 1,17,17,16, 
},
//[58] cell:10x3 
{
8,8, 0,17,17,0, 0,18,33,0, 0,18,33,0, 0,17,17,0, 0,17,17,0, 0,18,33,0, 0,18,33,0, 0,17,17,0, 
},
//[59] cell:11x3 
{
8,8, 0,17,17,0, 0,18,33,0, 0,18,33,0, 0,17,17,0, 0,18,33,0, 0,19,33,0, 0,1,33,0, 0,0,17,0, 
},
//[60] cell:12x3 
{
8,8, 0,0,18,16, 0,1,33,0, 0,18,16,0, 1,33,0,0, 0,18,16,0, 0,1,33,0, 0,0,18,16, 0,0,1,16, 
},
//[61] cell:13x3 
{
8,8, 0,0,0,0, 1,17,17,17, 1,34,34,33, 1,17,17,17, 1,34,34,33, 1,17,17,17, 0,0,0,0, 0,0,0,0, 
},
//[62] cell:14x3 
{
8,8, 1,33,0,0, 0,18,16,0, 0,1,33,0, 0,0,18,16, 0,1,33,0, 0,18,16,0, 1,33,0,0, 1,16,0,0, 
},
//[63] cell:15x3 
{
8,8, 0,17,17,16, 1,50,34,49, 1,33,17,33, 1,33,17,33, 1,17,34,49, 0,1,17,16, 0,1,33,0, 0,1,17,0, 
},
//[64] cell:0x4 
{
8,8, 1,34,35,16, 18,17,18,49, 33,50,33,33, 33,33,17,33, 33,50,33,33, 50,17,18,49, 19,34,35,17, 1,17,17,16, 
},
//[65] cell:1x4 
{
8,8, 1,17,17,16, 19,34,34,49, 18,49,19,33, 18,17,17,33, 18,34,34,33, 18,17,17,33, 18,16,1,33, 17,16,1,17, 
},
//[66] cell:2x4 
{
8,8, 17,17,17,16, 18,34,34,49, 18,17,19,33, 18,34,34,17, 18,17,19,33, 18,17,19,33, 18,34,34,49, 17,17,17,16, 
},
//[67] cell:3x4 
{
8,8, 1,17,17,17, 19,34,34,33, 18,49,17,17, 18,16,0,0, 18,16,0,0, 18,49,17,17, 19,34,34,33, 1,17,17,17, 
},
//[68] cell:4x4 
{
8,8, 17,17,17,16, 18,34,34,49, 18,17,19,33, 18,16,1,33, 18,16,1,33, 18,17,19,33, 18,34,34,49, 17,17,17,16, 
},
//[69] cell:5x4 
{
8,8, 17,17,17,17, 18,34,34,33, 18,17,17,17, 18,34,34,33, 18,17,17,17, 18,17,17,17, 18,34,34,33, 17,17,17,17, 
},
//[70] cell:6x4 
{
8,8, 17,17,17,17, 18,34,34,33, 18,17,17,17, 18,34,34,33, 18,17,17,17, 18,16,0,0, 18,16,0,0, 17,0,0,0, 
},
//[71] cell:7x4 
{
8,8, 1,17,17,17, 19,34,34,33, 18,49,17,17, 18,17,34,33, 18,17,17,33, 18,49,17,33, 19,34,34,33, 1,17,17,17, 
},
//[72] cell:8x4 
{
8,8, 17,16,1,17, 18,16,1,33, 18,17,17,33, 18,34,34,33, 18,17,17,33, 18,16,1,33, 18,16,1,33, 17,16,1,17, 
},
//[73] cell:9x4 
{
8,8, 0,17,17,16, 0,18,34,16, 0,17,33,16, 0,1,33,0, 0,1,33,0, 0,17,33,16, 0,18,34,16, 0,17,17,16, 
},
//[74] cell:10x4 
{
8,8, 0,1,17,17, 0,1,34,33, 0,1,18,17, 17,16,18,16, 18,16,18,16, 18,49,50,16, 19,34,35,16, 1,17,17,0, 
},
//[75] cell:11x4 
{
8,8, 17,16,1,17, 18,16,19,33, 18,17,50,16, 18,19,33,0, 18,50,35,16, 18,33,18,49, 18,16,1,33, 17,16,0,17, 
},
//[76] cell:12x4 
{
8,8, 17,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,16,0,0, 18,17,17,17, 18,34,34,33, 17,17,17,17, 
},
//[77] cell:13x4 
{
8,8, 17,0,0,17, 18,16,1,33, 18,33,18,33, 18,18,33,33, 18,17,17,33, 18,16,1,33, 18,16,1,33, 17,16,1,17, 
},
//[78] cell:14x4 
{
8,8, 17,0,1,17, 18,16,1,33, 18,33,1,33, 18,18,17,33, 18,17,33,33, 18,16,18,33, 18,16,1,33, 17,16,0,17, 
},
//[79] cell:15x4 
{
8,8, 1,17,17,16, 19,34,34,49, 18,49,19,33, 18,16,1,33, 18,16,1,33, 18,49,19,33, 19,34,34,49, 1,17,17,16, 
},
//[80] cell:0x5 
{
8,8, 17,17,17,16, 18,34,34,49, 18,17,19,33, 18,17,19,33, 18,34,34,49, 18,17,17,16, 18,16,0,0, 17,16,0,0, 
},
//[81] cell:1x5 
{
8,8, 1,17,17,16, 19,34,34,49, 18,49,19,33, 18,17,17,33, 18,17,33,33, 18,49,18,49, 19,34,35,33, 1,17,17,17, 
},
//[82] cell:2x5 
{
8,8, 17,17,17,16, 18,34,34,49, 18,17,19,33, 18,17,19,33, 18,34,34,49, 18,17,50,16, 18,16,19,33, 17,16,1,17, 
},
//[83] cell:3x5 
{
8,8, 1,17,17,17, 19,34,34,33, 18,49,17,17, 19,34,34,49, 1,17,19,33, 17,17,19,33, 18,34,34,49, 17,17,17,16, 
},
//[84] cell:4x5 
{
8,8, 1,17,17,17, 1,34,34,33, 1,17,33,17, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,1,17,0, 
},
//[85] cell:5x5 
{
8,8, 17,16,1,17, 18,16,1,33, 18,16,1,33, 18,16,1,33, 18,16,1,33, 18,49,19,33, 19,34,34,49, 1,17,17,16, 
},
//[86] cell:6x5 
{
8,8, 17,16,1,17, 18,16,1,33, 18,16,1,33, 18,16,1,33, 1,33,18,16, 1,35,50,16, 0,18,33,0, 0,1,16,0, 
},
//[87] cell:7x5 
{
8,8, 17,16,1,17, 18,16,1,33, 18,16,1,33, 18,17,17,33, 18,18,33,33, 18,33,18,33, 18,16,1,33, 17,0,0,17, 
},
//[88] cell:8x5 
{
8,8, 17,0,0,17, 18,16,1,33, 19,33,18,49, 1,50,35,16, 1,50,35,16, 19,33,18,49, 18,16,1,33, 17,0,0,17, 
},
//[89] cell:9x5 
{
8,8, 1,16,0,17, 1,33,1,33, 1,50,18,49, 0,19,35,16, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,1,17,0, 
},
//[90] cell:10x5 
{
8,8, 17,17,17,17, 18,34,34,33, 17,17,18,16, 0,1,33,0, 0,18,16,0, 1,33,17,17, 18,34,34,33, 17,17,17,17, 
},
//[91] cell:11x5 
{
8,8, 0,17,17,0, 0,18,33,0, 0,18,16,0, 0,18,16,0, 0,18,16,0, 0,18,16,0, 0,18,33,0, 0,17,17,0, 
},
//[92] cell:12x5 
{
8,8, 17,0,0,0, 18,16,0,0, 1,33,0,0, 0,18,16,0, 0,1,33,0, 0,0,18,16, 0,0,1,33, 0,0,0,17, 
},
//[93] cell:13x5 
{
8,8, 0,17,17,0, 0,18,33,0, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,18,33,0, 0,17,17,0, 
},
//[94] cell:14x5 
{
8,8, 0,0,16,0, 0,1,33,0, 0,18,18,16, 1,33,1,33, 1,16,0,17, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[95] cell:15x5 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 17,17,17,17, 18,34,34,33, 17,17,17,17, 
},
//[96] cell:0x6 
{
8,8, 0,17,17,0, 0,18,33,0, 0,18,49,0, 0,18,16,0, 0,17,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
//[97] cell:1x6 
{
8,8, 0,0,0,0, 0,17,17,16, 0,18,34,49, 0,17,19,33, 1,50,34,33, 1,33,17,33, 1,50,34,33, 0,17,17,17, 
},
//[98] cell:2x6 
{
8,8, 1,17,0,0, 1,33,0,0, 1,33,17,16, 1,35,34,49, 1,34,17,33, 1,33,17,33, 1,34,34,49, 1,17,17,16, 
},
//[99] cell:3x6 
{
8,8, 0,0,0,0, 0,17,17,17, 1,50,34,33, 1,33,17,17, 1,33,0,0, 1,33,17,17, 1,50,34,33, 0,17,17,17, 
},
//[100] cell:4x6 
{
8,8, 0,0,1,17, 0,0,1,33, 0,17,17,33, 1,50,35,33, 1,33,18,33, 1,33,17,33, 1,50,34,33, 0,17,17,17, 
},
//[101] cell:5x6 
{
8,8, 0,0,0,0, 0,17,17,16, 1,50,34,49, 1,33,17,33, 1,34,34,49, 1,33,17,17, 1,50,34,33, 0,17,17,17, 
},
//[102] cell:6x6 
{
8,8, 0,1,17,16, 0,19,34,16, 1,18,17,16, 1,34,34,16, 1,18,17,16, 0,18,16,0, 0,18,16,0, 0,17,16,0, 
},
//[103] cell:7x6 
{
8,8, 0,0,0,0, 0,17,17,17, 1,50,34,33, 1,33,17,33, 1,50,34,33, 1,17,17,33, 1,34,34,49, 1,17,17,16, 
},
//[104] cell:8x6 
{
8,8, 1,17,0,0, 1,33,0,0, 1,33,17,16, 1,35,34,49, 1,34,17,33, 1,33,1,33, 1,33,1,33, 1,17,1,17, 
},
//[105] cell:9x6 
{
8,8, 0,1,17,0, 0,1,33,0, 0,1,17,0, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,1,33,0, 0,1,17,0, 
},
//[106] cell:10x6 
{
8,8, 0,0,17,16, 0,0,18,16, 0,0,17,16, 0,0,18,16, 1,17,18,16, 1,33,18,16, 1,50,35,16, 0,17,17,0, 
},
//[107] cell:11x6 
{
8,8, 1,17,0,0, 1,33,0,17, 1,33,1,33, 1,33,18,16, 1,33,33,0, 1,34,50,16, 1,33,19,33, 1,17,1,17, 
},
//[108] cell:12x6 
{
8,8, 0,17,16,0, 0,18,49,0, 0,17,33,0, 0,1,33,0, 0,1,33,0, 0,1,33,16, 0,1,34,16, 0,1,17,16, 
},
//[109] cell:13x6 
{
8,8, 0,0,0,0, 1,17,17,16, 1,34,50,49, 1,33,33,33, 1,33,33,33, 1,33,33,33, 1,33,33,33, 1,17,17,17, 
},
//[110] cell:14x6 
{
8,8, 0,0,0,0, 1,17,17,16, 1,35,34,49, 1,34,17,33, 1,33,1,33, 1,33,1,33, 1,33,1,33, 1,17,1,17, 
},
//[111] cell:15x6 
{
8,8, 0,0,0,0, 0,17,17,16, 1,50,34,49, 1,33,17,33, 1,33,1,33, 1,33,17,33, 1,50,34,49, 0,17,17,16, 
},
//[112] cell:0x7 
{
8,8, 0,0,0,0, 1,17,17,16, 1,34,34,49, 1,33,17,33, 1,34,17,33, 1,35,34,49, 1,33,17,16, 1,17,0,0, 
},
//[113] cell:1x7 
{
8,8, 0,0,0,0, 0,17,17,17, 1,50,34,33, 1,33,17,33, 1,33,18,33, 1,50,35,33, 0,17,17,33, 0,0,1,17, 
},
//[114] cell:2x7 
{
8,8, 0,0,0,0, 1,17,0,0, 1,33,17,16, 1,35,34,49, 1,34,17,33, 1,33,1,17, 1,33,0,0, 1,17,0,0, 
},
//[115] cell:3x7 
{
8,8, 0,0,0,0, 0,17,17,17, 1,50,34,33, 1,33,17,17, 1,50,34,49, 1,17,17,33, 1,34,34,49, 1,17,17,16, 
},
//[116] cell:4x7 
{
8,8, 0,1,17,0, 1,17,33,17, 1,34,34,33, 1,17,33,17, 0,1,33,0, 0,1,33,17, 0,1,50,33, 0,0,17,17, 
},
//[117] cell:5x7 
{
8,8, 0,0,0,0, 1,17,1,17, 1,33,1,33, 1,33,1,33, 1,33,1,33, 1,33,18,33, 1,50,35,33, 0,17,17,17, 
},
//[118] cell:6x7 
{
8,8, 0,0,0,0, 1,17,1,17, 1,33,1,33, 1,50,18,49, 0,18,18,16, 0,19,35,16, 0,1,33,0, 0,0,16,0, 
},
//[119] cell:7x7 
{
8,8, 0,0,0,0, 1,17,17,17, 1,33,33,33, 1,33,33,33, 1,35,35,33, 0,18,50,16, 0,18,18,16, 0,1,1,0, 
},
//[120] cell:8x7 
{
8,8, 0,0,0,0, 1,16,0,17, 1,33,1,33, 1,50,18,49, 0,19,35,16, 1,50,18,49, 1,33,1,33, 1,16,0,17, 
},
//[121] cell:9x7 
{
8,8, 0,0,0,0, 1,17,1,17, 1,33,1,33, 1,50,18,49, 0,19,35,16, 0,18,49,0, 1,35,16,0, 1,17,0,0, 
},
//[122] cell:10x7 
{
8,8, 0,0,0,0, 1,17,17,17, 1,34,34,33, 1,17,18,16, 0,1,33,0, 0,18,17,17, 1,34,34,33, 1,17,17,17, 
},
//[123] cell:11x7 
{
8,8, 0,1,33,0, 0,18,17,0, 0,18,16,0, 1,33,0,0, 0,18,16,0, 0,18,16,0, 0,1,33,0, 0,0,17,0, 
},
//[124] cell:12x7 
{
8,8, 0,1,17,0, 0,1,33,0, 0,1,33,0, 0,1,17,0, 0,1,33,0, 0,1,33,0, 0,1,17,0, 0,0,0,0, 
},
//[125] cell:13x7 
{
8,8, 0,18,16,0, 0,17,33,0, 0,1,33,0, 0,0,18,16, 0,1,33,0, 0,1,33,0, 0,18,16,0, 0,17,0,0, 
},
//[126] cell:14x7 
{
8,8, 0,0,0,0, 0,0,0,0, 0,17,0,16, 1,34,17,33, 18,17,34,16, 1,0,17,0, 0,0,0,0, 0,0,0,0, 
},
//[127] cell:15x7 
{
8,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
},
};