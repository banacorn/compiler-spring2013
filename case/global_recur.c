int flag;
int count;
void f(){
	if(flag==0){
		return ;
	}
	else{
		write(flag);
		flag=flag-1;
		f();
	}
	return ;
}
void main(){
	write("Enter a num:\n");
	flag=read();
	f();
	write("\n");
	return ;
}
