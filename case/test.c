int a;

void g () {
    a = a - 1;
    write(a);

}

void f () {
    a = a - 1;
    write(a);
    g();
}

void main(){
    a = 5;
    f();
    return ;
}
