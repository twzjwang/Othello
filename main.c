#include <stdio.h>
#include <time.h>
#include "game.h"

int Deep = 2;
int valuation_table[64] = {  300, -60, 10, 10, 10, 10, -60,  300,
                            -60, -200,  5,  5,  5,  5, -200, -60,
                             10,   5,  1,  1,  1,  1,   5,  10,
                             10,   5,  1,  1,  1,  1,   5,  10,
                             10,   5,  1,  1,  1,  1,   5,  10,
                             10,   5,  1,  1,  1,  1,   5,  10,
                            -60, -200,  5,  5,  5,  5, -200, -60,
                             300, -60, 10, 10, 10, 10, -60,  300};

//ref http://wsothello.blogspot.tw/2010/07/opening-books.html
const char opening_book[400][40] = {
    "C4c3",
    "C4c3D3c5B2",
    "C4c3D3c5B3",
    "C4c3D3c5B3f4B5b4C6d6F5",
    "C4c3D3c5B4",
    "C4c3D3c5B4d2C2f4D6c6F5e6F7",
    "C4c3D3c5B4d2D6",
    "C4c3D3c5B4d2E2",
    "C4c3D3c5B4e3",
    "C4c3D3c5B5",
    "C4c3D3c5B6c6B5",
    "C4c3D3c5B6e3",
    "C4c3D3c5D6",
    "C4c3D3c5D6e3",
    "C4c3D3c5D6f4B4",
    "C4c3D3c5D6f4B4b6B5c6B3",
    "C4c3D3c5D6f4B4b6B5c6F5",
    "C4c3D3c5D6f4B4c6B5b3B6e3C2a4A5a6D2",
    "C4c3D3c5D6f4B4e3B3",
    "C4c3D3c5D6f4F5",
    "C4c3D3c5D6f4F5d2",
    "C4c3D3c5D6f4F5d2B5",
    "C4c3D3c5D6f4F5d2G4d7",
    "C4c3D3c5D6f4F5e6C6d7",
    "C4c3D3c5D6f4F5e6F6",
    "C4c3D3c5F6",
    "C4c3D3c5F6e2C6",
    "C4c3D3c5F6e3C6f5F4g5",
    "C4c3D3c5F6f5",
    "C4c3D3e3B2",
    "C4c3D3e3C2",
    "C4c3D3e3C2d6E2d2F3f4E6",
    "C4c3D3e3D2",
    "C4c3D3e3D2b4B3d6F4f3E6f5G6",
    "C4c3D3e3D2b4B5",
    "C4c3D3e3D2b4F4",
    "C4c3D3e3D2c5",
    "C4c3D3e3E2",
    "C4c3D3e3F2c5",
    "C4c3D3e3F2f3E2",
    "C4c3D3e3F4 ",
    "C4c3D3e3F4c5 ",
    "C4c3D3e3F4d6D2",
    "C4c3D3e3F4d6D2c5C2",
    "C4c3D3e3F4d6D2f2E2f3C2",
    "C4c3D3e3F4d6D2f2E2f3E6",
    "C4c3D3e3F4d6D2f3E2c2F2c5B3d1E1f1B4",
    "C4c3D3e3F4d6E6",
    "C4c3D3e3F4d6E6b4 ",
    "C4c3D3e3F4d6E6b4D7g4",
    "C4c3D3e3F4d6E6b4E2",
    "C4c3D3e3F4d6E6f5F3g4",
    "C4c3D3e3F4d6E6f5F6",
    "C4c3D3e3F6",
    "C4c3D3e3F6b5F3 ",
    "C4c3D3e3F6c5F3e6D6e7",
    "C4c3D3e3F6e6",
    "C4c3E6c5",
    "C4c3F5c5",
    "C4c5",
    "C4e3",
    "C4e3F4c5D6e6",
    "C4e3F4c5D6f3C6",
    "C4e3F4c5D6f3D3",
    "C4e3F4c5D6f3D3c3",
    "C4e3F4c5D6f3E2",
    "C4e3F4c5D6f3E6c3D3e2",
    "C4e3F4c5D6f3E6c3D3e2B5",
    "C4e3F4c5D6f3E6c3D3e2B5f5",
    "C4e3F4c5D6f3E6c3D3e2B5f5B3",
    "C4e3F4c5D6f3E6c3D3e2B5f5B4f6C2e7D2c7",
    "C4e3F4c5D6f3E6c3D3e2B6f5",
    "C4e3F4c5D6f3E6c3D3e2B6f5B4f6G5d7",
    "C4e3F4c5D6f3E6c3D3e2B6f5G5",
    "C4e3F4c5D6f3E6c3D3e2B6f5G5f6",
    "C4e3F4c5D6f3E6c3D3e2D2",
    "C4e3F4c5D6f3E6c6",
    "C4e3F4c5E6",
    "C4e3F5b4",
    "C4e3F5b4F3",
    "C4e3F5b4F3f4E2e6G5f6D6c6",
    "C4e3F5e6D3",
    "C4e3F5e6F4",
    "C4e3F5e6F4c5D6c6F7f3",
    "C4e3F5e6F4c5D6c6F7g5G6",
    "C4e3F6b4",
    "C4e3F6e6F5",
    "C4e3F6e6F5c5C3",
    "C4e3F6e6F5c5C3b4",
    "C4e3F6e6F5c5C3b4D6c6B5a6B6c7",
    "C4e3F6e6F5c5C3c6",
    "C4e3F6e6F5c5C3g5",
    "C4e3F6e6F5c5D3",
    "C4e3F6e6F5c5D6",
    "C4e3F6e6F5c5F4g5G4f3C6d3D6",
    "C4e3F6e6F5c5F4g5G4f3C6d3D6b3C3b4E2b6",
    "C4e3F6e6F5c5F4g6F7",
    "C4e3F6e6F5c5F4g6F7d3",
    "C4e3F6e6F5g6 ",
    "D3c3",
    "D3c3C4c5B2",
    "D3c3C4c5B3",
    "D3c3C4c5B3f4B5b4C6d6F5",
    "D3c3C4c5B4",
    "D3c3C4c5B4d2C2f4D6c6F5e6F7",
    "D3c3C4c5B4d2D6",
    "D3c3C4c5B4d2E2",
    "D3c3C4c5B4e3",
    "D3c3C4c5B5",
    "D3c3C4c5B6c6B5",
    "D3c3C4c5B6e3",
    "D3c3C4c5D6",
    "D3c3C4c5D6e3",
    "D3c3C4c5D6f4B4",
    "D3c3C4c5D6f4B4b6B5c6B3",
    "D3c3C4c5D6f4B4b6B5c6F5",
    "D3c3C4c5D6f4B4c6B5b3B6e3C2a4A5a6D2",
    "D3c3C4c5D6f4B4e3B3",
    "D3c3C4c5D6f4F5",
    "D3c3C4c5D6f4F5d2",
    "D3c3C4c5D6f4F5d2B5",
    "D3c3C4c5D6f4F5d2G4d7",
    "D3c3C4c5D6f4F5e6C6d7",
    "D3c3C4c5D6f4F5e6F6",
    "D3c3C4c5F6",
    "D3c3C4c5F6e2C6",
    "D3c3C4c5F6e3C6f5F4g5",
    "D3c3C4c5F6f5",
    "D3c3C4e3B2",
    "D3c3C4e3C2",
    "D3c3C4e3C2d6E2d2F3f4E6",
    "D3c3C4e3D2",
    "D3c3C4e3D2b4B3d6F4f3E6f5G6",
    "D3c3C4e3D2b4B5",
    "D3c3C4e3D2b4F4",
    "D3c3C4e3D2c5",
    "D3c3C4e3E2",
    "D3c3C4e3F2c5",
    "D3c3C4e3F2f3E2",
    "D3c3C4e3F4",
    "D3c3C4e3F4c5",
    "D3c3C4e3F4d6D2",
    "D3c3C4e3F4d6D2c5C2",
    "D3c3C4e3F4d6D2f2E2f3C2",
    "D3c3C4e3F4d6D2f2E2f3E6",
    "D3c3C4e3F4d6D2f3E2c2F2c5B3d1E1f1B4",
    "D3c3C4e3F4d6E6",
    "D3c3C4e3F4d6E6b4",
    "D3c3C4e3F4d6E6b4D7g4",
    "D3c3C4e3F4d6E6b4E2",
    "D3c3C4e3F4d6E6f5F3g4",
    "D3c3C4e3F4d6E6f5F6",
    "D3c3C4e3F6",
    "D3c3C4e3F6b5F3",
    "D3c3C4e3F6c5F3e6D6e7",
    "D3c3C4e3F6e6",
    "D3c3E6e3",
    "D3c3F5e3",
    "D3c5",
    "D3c5D6e3F4c6B5",
    "D3c5D6e3F4c6C4",
    "D3c5D6e3F4c6C4c3",
    "D3c5D6e3F4c6F3",
    "D3c5D6e3F4c6F5c3C4b5",
    "D3c5D6e3F4c6F5c3C4b5B4",
    "D3c5D6e3F4c6F5c3C4b5E2",
    "D3c5D6e3F4c6F5c3C4b5E2e6",
    "D3c5D6e3F4c6F5c3C4b5E2e6C2",
    "D3c5D6e3F4c6F5c3C4b5E2e6D2f6B3g5B4g3",
    "D3c5D6e3F4c6F5c3C4b5F2e6",
    "D3c5D6e3F4c6F5c3C4b5F2e6D2f6E7g4",
    "D3c5D6e3F4c6F5c3C4b5F2e6E7",
    "D3c5D6e3F4c6F5c3C4b5F2e6E7f6",
    "D3c5D6e3F4c6F5f3",
    "D3c5D6e3F4f5",
    "D3c5D6e3F5",
    "D3c5E6d2",
    "D3c5E6d2C6",
    "D3c5E6d2C6d6B5f5E7f6F4f3",
    "D3c5E6f5C4",
    "D3c5E6f5D6",
    "D3c5E6f5D6e3F4f3G6c6",
    "D3c5E6f5D6e3F4f3G6e7F7",
    "D3c5F6d2",
    "D3c5F6f5E6",
    "D3c5F6f5E6e3C3",
    "D3c5F6f5E6e3C3d2",
    "D3c5F6f5E6e3C3d2F4f3E2f1F2g3",
    "D3c5F6f5E6e3C3e7",
    "D3c5F6f5E6e3C3f3",
    "D3c5F6f5E6e3C4",
    "D3c5F6f5E6e3D6e7D7c6F3c4F4",
    "D3c5F6f5E6e3D6e7D7c6F3c4F4c2C3d2B5f2",
    "D3c5F6f5E6e3D6f7G6",
    "D3c5F6f5E6e3D6f7G6c4",
    "D3c5F6f5E6e3F4",
    "D3c5F6f5E6f7",
    "D3e3",
    "E6d6",
    "E6f4",
    "E6f4C3c4D3",
    "E6f4C3c4D3c2",
    "E6f4C3c4D3d6C5",
    "E6f4C3c4D3d6E3c2B3",
    "E6f4C3c4D3d6E3c2B3f5",
    "E6f4C3c4D3d6E3d2E2f3C6f5C5",
    "E6f4C3c4D3d6E3d2E2f3C6f5C5f7F6e7G4c7",
    "E6f4C3c4D3d6F5",
    "E6f4C3c4D3d6F6",
    "E6f4C3c4D3d6F6c6",
    "E6f4C3c4D3d6F6d2",
    "E6f4C3c4D3d6F6e7",
    "E6f4C3c4D3d6F6e7C5c6D7c8C7b6",
    "E6f4C3e7",
    "E6f4D3c4E3",
    "E6f4D3c4E3d6C5c6B3d2C2",
    "E6f4D3c4E3d6C5c6B3f3",
    "E6f4D3c4F5",
    "E6f4D3e7",
    "E6f4D3e7F3",
    "E6f4D3e7F3e3G4c4D2c3C5c6",
    "E6f4E3d6C4",
    "E6f4E3d6C5c4",
    "E6f4E3d6C5f3C4c6",
    "E6f4E3d6C5f3C4f6F5g4",
    "E6f4E3d6C5f3C4f6F5g4C7d3",
    "E6f4E3d6C5f3C4f6F5g4C7d3D2",
    "E6f4E3d6C5f3C4f6F5g4C7d3D2c3",
    "E6f4E3d6C5f3C4f6F5g4C7d3E7c3D2b5",
    "E6f4E3d6C5f3C4f6F5g4D7",
    "E6f4E3d6C5f3C4f6F5g4D7d3",
    "E6f4E3d6C5f3C4f6F5g4D7d3E7c3G6b4G5b6",
    "E6f4E3d6C5f3C4f6F5g4D7d3F7",
    "E6f4E3d6C5f3C4f6F5g4G5",
    "E6f4E3d6C5f3C6",
    "E6f4E3d6C5f3F5",
    "E6f4E3d6C5f3F5f6",
    "E6f4E3d6C5f3G4",
    "E6f6",
    "E6f6C4d6",
    "E6f6D3d6",
    "E6f6F5d6C3",
    "E6f6F5d6C3d3",
    "E6f6F5d6C3f4C6d3E3d2",
    "E6f6F5d6C3g4C6",
    "E6f6F5d6C5",
    "E6f6F5d6C5e3D3",
    "E6f6F5d6C5e3D3c4C3",
    "E6f6F5d6C5e3D3c4C6b5",
    "E6f6F5d6C5e3D3g5",
    "E6f6F5d6C5e3D3g5D7",
    "E6f6F5d6C5e3D3g5E2b5",
    "E6f6F5d6C5e3E7",
    "E6f6F5d6C5e3E7c6D7f7C7f4G6e8D8c8G5",
    "E6f6F5d6C5e3E7c7D7c6D3",
    "E6f6F5d6C5e3E7c7D7c6F7",
    "E6f6F5d6C5e3E7f4F7",
    "E6f6F5d6C5f4",
    "E6f6F5d6C7c6D7",
    "E6f6F5d6C7f4",
    "E6f6F5d6D7",
    "E6f6F5d6E7",
    "E6f6F5d6E7f4",
    "E6f6F5d6E7g5C5",
    "E6f6F5d6E7g5G4",
    "E6f6F5d6E7g5G6e3C5c6D3c4B3",
    "E6f6F5d6F7",
    "E6f6F5d6F7e3D7e7C6c5D3",
    "E6f6F5d6G7",
    "E6f6F5f4C3",
    "E6f6F5f4C3c4",
    "E6f6F5f4C3d6F3c4C5b4",
    "E6f6F5f4C3d7F3",
    "E6f6F5f4E3",
    "E6f6F5f4E3c5C4",
    "E6f6F5f4E3c5C4d3C3",
    "E6f6F5f4E3c5C4d3F3e2",
    "E6f6F5f4E3c5C4e7",
    "E6f6F5f4E3c5C4e7B5e2",
    "E6f6F5f4E3c5C4e7G4",
    "E6f6F5f4E3c5G5",
    "E6f6F5f4E3c5G5d6G6",
    "E6f6F5f4E3c5G5f3G4g6G3d6F7h5H4h3E7",
    "E6f6F5f4E3c5G5g3G4f3C4",
    "E6f6F5f4E3c5G5g3G4f3G6",
    "E6f6F5f4E3d6",
    "E6f6F5f4G3d6",
    "E6f6F5f4G3f3G4",
    "E6f6F5f4G4",
    "E6f6F5f4G5",
    "E6f6F5f4G5d6",
    "E6f6F5f4G5e7D7",
    "E6f6F5f4G5e7E3",
    "E6f6F5f4G5e7F7c5E3f3C4d3C2",
    "E6f6F5f4G6",
    "E6f6F5f4G6c5G4g5F3e3C4",
    "E6f6F5f4G7",
    "F5d6",
    "F5d6C3d3C4",
    "F5d6C3d3C4b3",
    "F5d6C3d3C4f4C5b3C2",
    "F5d6C3d3C4f4C5b3C2e6",
    "F5d6C3d3C4f4C5b4B5c6F3e6E3",
    "F5d6C3d3C4f4C5b4B5c6F3e6E3g6F6g5D7g3",
    "F5d6C3d3C4f4E3",
    "F5d6C3d3C4f4E6",
    "F5d6C3d3C4f4F6",
    "F5d6C3d3C4f4F6b4",
    "F5d6C3d3C4f4F6f3",
    "F5d6C3d3C4f4F6g5",
    "F5d6C3d3C4f4F6g5E3f3G4h3G3f2",
    "F5d6C3g5",
    "F5d6C4d3C5",
    "F5d6C4d3C5f4E3f3C2b4B3",
    "F5d6C4d3C5f4E3f3C2c6",
    "F5d6C4d3E6",
    "F5d6C4g5",
    "F5d6C4g5C6",
    "F5d6C4g5C6c5D7d3B4c3E3f3",
    "F5d6C5f4D3",
    "F5d6C5f4E3c6D3f3",
    "F5d6C5f4E3c6D3f6E6d7",
    "F5d6C5f4E3c6D3f6E6d7E7",
    "F5d6C5f4E3c6D3f6E6d7G3c4",
    "F5d6C5f4E3c6D3f6E6d7G3c4B4",
    "F5d6C5f4E3c6D3f6E6d7G3c4B4c3",
    "F5d6C5f4E3c6D3f6E6d7G3c4G5c3B4e2",
    "F5d6C5f4E3c6D3f6E6d7G4",
    "F5d6C5f4E3c6D3f6E6d7G4c4",
    "F5d6C5f4E3c6D3f6E6d7G4c4G5c3F7d2E7f2",
    "F5d6C5f4E3c6D3f6E6d7G4c4G6",
    "F5d6C5f4E3c6D7",
    "F5d6C5f4E3c6E6",
    "F5d6C5f4E3c6E6f6",
    "F5d6C5f4E3c6F3",
    "F5d6C5f4E3d3",
    "F5f4",
    "F5f6",
    "F5f6C4f4",
    "F5f6D3f4",
    "F5f6E6d6C3",
    "F5f6E6d6C3d3",
    "F5f6E6d6C3f4C6d3E3d2",
    "F5f6E6d6C3g4C6",
    "F5f6E6d6C5",
    "F5f6E6d6C5e3D3",
    "F5f6E6d6C5e3D3c4C3",
    "F5f6E6d6C5e3D3c4C6b5",
    "F5f6E6d6C5e3D3g5",
    "F5f6E6d6C5e3D3g5D7",
    "F5f6E6d6C5e3D3g5E2b5",
    "F5f6E6d6C5e3E7",
    "F5f6E6d6C5e3E7c6D7f7C7f4G6e8D8c8G5",
    "F5f6E6d6C5e3E7c7D7c6D3",
    "F5f6E6d6C5e3E7c7D7c6F7",
    "F5f6E6d6C5e3E7f4F7",
    "F5f6E6d6C5f4",
    "F5f6E6d6C7c6D7",
    "F5f6E6d6C7f4",
    "F5f6E6d6D7",
    "F5f6E6d6E7",
    "F5f6E6d6E7f4",
    "F5f6E6d6E7g5C5",
    "F5f6E6d6E7g5G4",
    "F5f6E6d6E7g5G6e3C5c6D3c4B3",
    "F5f6E6d6F7",
    "F5f6E6d6F7e3D7e7C6c5D3",
    "F5f6E6d6G7",
    "F5f6E6f4C3",
    "F5f6E6f4C3c4",
    "F5f6E6f4C3d6F3c4C5b4",
    "F5f6E6f4C3d7F3",
    "F5f6E6f4E3",
    "F5f6E6f4E3c5C4",
    "F5f6E6f4E3c5C4d3C3",
    "F5f6E6f4E3c5C4d3F3e2",
    "F5f6E6f4E3c5C4e7",
    "F5f6E6f4E3c5C4e7B5e2",
    "F5f6E6f4E3c5C4e7G4",
    "F5f6E6f4E3c5G5",
    "F5f6E6f4E3c5G5d6G6",
    "F5f6E6f4E3c5G5f3G4g6G3d6F7h5H4h3E7",
    "F5f6E6f4E3c5G5g3G4f3C4",
    "F5f6E6f4E3c5G5g3G4f3G6",
    "F5f6E6f4E3d6",
    "F5f6E6f4G3d6",
    "F5f6E6f4G3f3G4",
    "F5f6E6f4G4",
    "F5f6E6f4G5",
    "F5f6E6f4G5d6",
    "F5f6E6f4G5e7D7",
    "F5f6E6f4G5e7E3",
    "F5f6E6f4G5e7F7c5E3f3C4d3C2",
    "F5f6E6f4G6",
    "F5f6E6f4G6c5G4g5F3e3C4",
    "F5f6E6f4G7"};

int black_mode, white_mode; //0:opening 1:a-b searching
int book_start, book_end;

//return next step according to opening book result
int opening(char process[], char color);

//return next step according to a-b searching result
int absearch(char board[], char color, int deep);

//return evaluation value
int evaluation_function(char board[], char color);

//return value
int evaluated_value(char board[], char color);

//return mobility
int evaluated_mobility(char board[], char color);

//return stability
int evaluated_stability(char board[], char color);

//sim move
int sim_move(char board[], int index, char color);

int main()
{
    int input = 1;
    int d, ai_move;
    char c;
    printf("Black : (1) Player (2) AI\n");
    scanf("%d", &input);
    getchar();
    if (input == 1)
        is_black_ai = 0;
    else
        is_black_ai = 1;
    printf("White : (1) Player (2) AI\n");
    scanf("%d", &input);
    getchar();
    if (input == 1)
        is_white_ai = 0;
    else
        is_white_ai = 1;

    init_board();
    srand(time(NULL));
    black_mode = 0;
    white_mode = 0;
    book_start = 0;
    book_end = 395;

    while (!is_gameover) {
        print_board();
        if ((black_score + white_score) % 14 == 0)
            Deep += 2;

        printf("black %d value %d mobility %d\n", evaluation_function(board, 'x'), evaluated_value(board, 'x'), evaluated_mobility(board, 'x'));
        printf("white %d value %d mobility %d\n", evaluation_function(board, 'o'), evaluated_value(board, 'o'), evaluated_mobility(board, 'o'));
        printf("\n");
        if (!turn && !is_black_ai) {
            printf("Input black's move (e.x. 'd3') : \a");
            scanf("%c%d", &c, &d);
            getchar();
            move((c - 'a')  + (d - 1) * 8, 'x');
        }
        else if (!turn && is_black_ai) {
            if (!black_mode) {
                printf("opening book\n");
                ai_move = opening(history, 'b');
                if (ai_move == -1)
                    black_mode = 1;
                else {
                    move(ai_move, 'x');
                }
            }
            if (black_mode){
                printf("a-b search deep %d\n", Deep);
                move(absearch(board, 'x', 0), 'x');
//getchar();
            }
        }
        else if (turn && !is_white_ai) {
            printf("Input white's move (e.x. 'd3') : \a");
            do {
                scanf("%c%d", &c, &d);
            } while (c < 'a' || c > 'h' || d < 1 || d > 8);
            getchar();
            move((c - 'a')  + (d - 1) * 8, 'o');
        }
        else {
            if (!white_mode) {
                printf("opening book\n");
                ai_move = opening(history, 'w');
                if (ai_move == -1)
                    white_mode = 1;
                else {
                    move(ai_move, 'o');
                }
            }
            if (white_mode){
                printf("a-b search deep %d\n", Deep);
                move(absearch(board, 'o', 0), 'o');
//getchar();
            }
        }
    }
    print_board();
    if (black_score > white_score)
        printf("Black Win!\n");
    else if (black_score < white_score)
        printf("White Win!\n");
    else
        printf("Even!\n");
}

//return next step according to opening book
int opening(char process[], char color)
{
    int step = black_score + white_score - 5;
    int i, temp; 
    char c, d;   
    if (step > 0)
    {
        c = process[step * 2 - 2];
        d = process[step * 2 - 1];
        while (opening_book[book_start][step * 2 - 2] != c || opening_book[book_start][step * 2 - 1] != d) {
            book_start ++;
            if (book_start > 395)
                return -1;
        }
        book_end = book_start;
        c = process[step * 2];
        d = process[step * 2 + 1];
        while (opening_book[book_start][step * 2] != c || opening_book[book_start][step * 2 + 1] != d) {
            book_start ++;
            if (book_start > 395)
                return -1;
        }
        book_end = book_start;
        while (opening_book[book_end][step * 2] == c || opening_book[book_end][step * 2 + 1] == d) {
            book_end ++;
            if (book_start > 395)
                return -1;
        }
        book_end--;
    }
    temp = rand() % (book_end - book_start + 1) + book_start;
    if (color == 'b' && opening_book[temp][step * 2 + 2] <= 'Z' && opening_book[temp][step * 2 + 2] >= 'A' && opening_book[temp][step * 2 + 3] <= '8' && opening_book[temp][step * 2 + 3] >= '1') {        
        return opening_book[temp][step * 2 + 2] - 'A' + (opening_book[temp][step * 2 + 3] - '1') * 8;
    } else if (color == 'w' && opening_book[temp][step * 2 + 2] <= 'z' && opening_book[temp][step * 2 + 2] >= 'a' && opening_book[temp][step * 2 + 3] <= '8' && opening_book[temp][step * 2 + 3] >= '1'){        
        return opening_book[temp][step * 2 + 2] - 'a' + (opening_book[temp][step * 2 + 3] - '1') * 8;
    }
    return -1;
}

//return next step according to a-b searching result
int absearch(char board[], char color, int deep)
{
    int i, max_pos, max_value, temp_value;
    char reverse_color = (color=='o') ? 'x' : 'o';
    char test_board[64];
    max_value = -99999999;
    if (deep > Deep)
        return -evaluation_function(board, color);

    for (i = 0; i < 64; i++) {
        strcpy(test_board, board);
        if(!sim_move(test_board, i, (deep % 2) ? reverse_color : color)){
//printf("deep %d i %d ", deep , i);
            temp_value = -absearch(test_board, color, deep + 1);
//printf("v %d\n", temp_value);
            if (temp_value >= max_value) {
                max_value = temp_value;
                max_pos = i;
            }
        }
    }
    //printf("d %d p %d v %d\n", deep, max_pos, max_value);
    if (deep)
        return max_value;
    //printf("max p %d v %d\n", max_pos, max_value);
    return max_pos;
}

//return evaluation function value
int evaluation_function(char board[], char color)
{
    int score, step = black_score + white_score;
    if (color == 'x')
        score = black_score - white_score;
    else
        score = white_score - black_score;

    return evaluated_value(board, color) * step + evaluated_mobility(board, color) * 2 + score * ((step > 55) ? 500 : step);
}

//value
int evaluated_value(char board[], char color)
{
    int i, value = 0;
    for (i = 0; i < 64; i++) {
        if (board[i] == ' ');
        else if (board[i] == color)
            value += valuation_table[i];
        else
            value -= valuation_table[i];
    }
    return value;
}

//return mobility
int evaluated_mobility(char board[], char color)
{
    int sum = 0, index, i;
    int mode = 0, temp_id, is_reverse = 0;
    char reverse_color = (color=='o') ? 'x' : 'o';

    for (index = 0; index < 64; index++) {
        if (board[index] != ' ') {
            continue;
        }
        is_reverse = 0;
        //reverse up
        mode = 0;
        temp_id = index;
        while (temp_id - 8 >= 0 && mode < 2) {
            temp_id -= 8;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse down
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id + 8 < 64 && mode < 2) {
            temp_id += 8;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse left
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id - 1 >= index / 8 * 8 && mode < 2) {
            temp_id--;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse right
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id + 1 < (index / 8 * 8 + 8) && mode < 2) {
            temp_id++;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse upleft
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id - 9 >= 0 && (temp_id - 9) % 8 < index % 8 && mode < 2) {
            temp_id -= 9;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse upright
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id - 7 >= 0 && (temp_id - 7) % 8 > index % 8 && mode < 2) {
            temp_id -= 7;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse downleft
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id + 7 >= 0 && (temp_id + 7) % 8 < index % 8 && mode < 2) {
            temp_id += 7;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse downright
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id + 9 >= 0 && (temp_id + 9) % 8 > index % 8 && mode < 2) {
            temp_id += 9;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        if (is_reverse) {
            sum++;
            continue;
        }
    }
    return sum;
}

//return stability
int evaluated_stability(char board[], char color)
{

}

//sim move
int sim_move(char board[], int index, char color)
{
    int mode = 0, temp_id, is_reverse = 0;
    char reverse_color = (color=='o') ? 'x' : 'o';

    if (board[index] != ' ') {
        return -1;
    }

    //reverse up
    mode = 0;
    temp_id = index;
    while (temp_id - 8 >= 0 && mode < 2) {
        temp_id -= 8;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id + 8; mode == 2 && i < index; i += 8)
        board[i] = color;

    //reverse down
    mode = 0;
    temp_id = index;
    while (temp_id + 8 < 64 && mode < 2) {
        temp_id += 8;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id - 8; mode == 2 && i > index; i -= 8)
        board[i] = color;

    //reverse left
    mode = 0;
    temp_id = index;
    while (temp_id - 1 >= index / 8 * 8 && mode < 2) {
        temp_id--;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id + 1; mode == 2 && i < index; i++)
        board[i] = color;

    //reverse right
    mode = 0;
    temp_id = index;
    while (temp_id + 1 < (index / 8 * 8 + 8) && mode < 2) {
        temp_id++;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id - 1; mode == 2 && i > index; i--)
        board[i] = color;

    //reverse upleft
    mode = 0;
    temp_id = index;
    while (temp_id - 9 >= 0 && (temp_id - 9) % 8 < index % 8 && mode < 2) {
        temp_id -= 9;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id + 9; mode == 2 && i < index; i += 9)
        board[i] = color;

    //reverse upright
    mode = 0;
    temp_id = index;
    while (temp_id - 7 >= 0 && (temp_id - 7) % 8 > index % 8 && mode < 2) {
        temp_id -= 7;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id + 7; mode == 2 && i < index; i += 7)
        board[i] = color;

    //reverse downleft
    mode = 0;
    temp_id = index;
    while (temp_id + 7 >= 0 && (temp_id + 7) % 8 < index % 8 && mode < 2) {
        temp_id += 7;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id - 7; mode == 2 && i > index; i -= 7)
        board[i] = color;

    //reverse downright
    mode = 0;
    temp_id = index;
    while (temp_id + 9 >= 0 && (temp_id + 9) % 8 > index % 8 && mode < 2) {
        temp_id += 9;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id - 9; mode == 2 && i > index; i -= 9)
        board[i] = color;

    if (is_reverse) {
        board[index] = color;
        return 0;
    } else {
        return -1;
    }
}

