int main()
{
    int index;
    write("Loop index:");
    index = read();
    while(index > 0){
        if(index/2 > 1){write("greater");}
        else {write("lower");}
        index = index - 1;
    }

    return 0;
}
