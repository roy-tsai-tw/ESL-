











Bugs:

1.TLM 2.0由CPU傳data(source addr, target addr, size, start_clear)到dma接收到的都是一個同樣的值(428550D4)
原因: 在cpu.h中我將SOURCE、TARGET、SIZE、START_CLEAR設為sc_uint<32>的型態，但在dma.h中是使用int型態的變數tmp_data來接收。
解法: 將cpu.h中的sc_uint<32>型態改為unsigned int即可。

2.
















