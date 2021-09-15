void extend_gcd(int a,int b,int &x,int &y)
{
    if(b == 0){
        x=1;
        y=0;
        return;
    }
    extend_gcd(b,a%b,x,y);
    int tmp = x;
    x = y;
    y = tmp - (a/b)*y;
}
/*

若要求 x 的最小正整数解可在求出ax+by=n的解(x,y)后，令 x = (x%b + b) % b , y = (n - a*x) / b
若要求 y 的最小正整数解可在求出ax+by=n的解(x,y)后，令 y = (y%a + a) % a , x = (n-b*y) / a

*/

