    #include <iostream>
    #include <vector>
    #include <string>
    #include <cmath>

    using namespace std;

    class point{
        public:
        point(double a = 0.0, double b = 0.0): x(a), y(b) {}
        void setx(double a){x=a;}
        void sety(double b){y=b;}
        double getx() const {return x;}
        double gety() const {return y;}
        
        private:
        double x, y;
    };

    double getDistance(const point& o1, const point& o2) {
            return sqrt(pow(o1.getx() - o2.getx(), 2) + pow(o1.gety() - o2.gety(), 2));
        }

    class Shape{
        public:
        
        virtual double getArea() const = 0;
        virtual double getPerimeter() const = 0;
        virtual ~Shape(){}
    };

    class triangle : public Shape{
        public:
        triangle(point _a, point _b, point _c): a(_a), b(_b), c(_c){};
        triangle(double x1,  double y1, double x2,  double y2, double x3,  double y3): a(x1, y1), b(x2, y2), c(x3, y3){};
        virtual double getArea() const override {
            double s1 = getDistance(a, b);
            double s2 = getDistance(b, c);
            double s3 = getDistance(a, c);
            double s = (s1+s2+s3)/2.0;
            return sqrt(s * (s - s1) * (s - s2) * (s - s3));
        }
        virtual double getPerimeter() const override{
            double s1 = getDistance(a, b);
            double s2 = getDistance(b, c);
            double s3 = getDistance(a, c);
            return s1 + s2 + s3;
        }
        virtual ~triangle() override {}
        private:
        point a;
        point b;
        point c;


    };

    class circle : public Shape{
        public:
        circle(point _o, int _r) : o(_o){setRadius(_r);}
        circle(double x, double y, int _r) : o(x, y){setRadius(_r);}
        double getArea() const override {
            return 3.14 * radius * radius; 
        }
        virtual double getPerimeter() const override {
            return 3.14 * radius * radius; 
        }
        void setRadius(int x){
            if(x<0) return;
            radius = x;
        }
        virtual int foo(){return 1;}
        virtual ~circle(){}
        private:
        point o;
        int radius;
    };

    double sum(vector<Shape*> vec){
        double res = 0.0;
        for(auto x : vec){
            res+=x->getArea();
        }
        return res;
    }
    class cir: public circle{
        public:
        cir(point _o, int _r) : circle(_o, _r){}
        cir(double x, double y, int _r) : circle(x, y, _r){}
        double getArea() const override {
            return 0;
        }
        int foo(){return 2;}
    
        
    };

    class cir2 : public circle {
    public:
        cir2(point _o, int _r) : circle(_o, _r) {}
        cir2(double x, double y, int _r) : circle(x, y, _r) {}
        double getArea() const override {
            return 42;  // Some other implementation in cir2
        }
        int foo(){return 3;}
    };


    int main(){
        circle* ptr;
        cir c(1.0, 1.0, 5);
        cir2 c2(2.0, 2.0, 7);
        ptr = &c2;
        cout<<ptr->foo();
    }
    /*

        circle a(1.0, 1.0, 5);
        triangle b(0.0, 4.0, 3.0, 0.0, 0.0, 0.0);
        vector <Shape*> vec;
        cir c(1.0, 1.0, 5);
        cir x(c);
        //cout<<x.getArea();
        vec.push_back(&a);
        vec.push_back(&b);
        vec.push_back(&c);
        cout<<sum(vec)<<endl;
        //cout<<b.getArea();
    }
*/
