#include <iostream>
#include "executor.h"

uint_16 op(uint_16 o)
{
    EndianMachine e;
    if (e.isBigEndian())
        return o;

    return ((uint_16 *)((uint_8[2]) {((pointer) &o)[1], ((pointer) &o)[0]}))[0];
}

int main() {
    MvM::Init();
    uint_16 for_loop[] = {
            op(iconst_0),
            op(istore_0),
            op(iconst_12),
            op(istore_1),
//
            op(mark), 0,
            op(iload_0),
            op(iload_1),
//
            op(icmple_i),
            op(if_t), 0, op(20),

            op(iconst_6),
            op(iload_0),
            op(imul_i),
            op(iprint),
            op(newline),

            op(iinc_1), 0,

            op(jumptomark), 0,

            op(iconst_0),
            op(iconst_12),
    };

    uint_16 ops[] = {op(iconst), op(0), op(20), op(iprint)};
    uint_64 length = sizeof(for_loop);

    pointer base = new unsigned char[4];
    Stack stack;

    MvM::execute(new OP_STACK[2], new MochaNativeInterface*[2], base, base, stack, OP_STACK((uint_8*) for_loop, length));

    return 0;
}