fn main() {
    fn f(n: i32) -> i32 {
        n + 42
    }
    fn g(n: i32) -> i32 {
        n * 2
    }
    fn compose(x:i32,f: fn(i32) -> i32, g:fn(i32) -> i32) -> i32 {
        return f(g(x));
    }
    //let n = 1;
    //println!("{}",compose(n,f,g));
    println!("{}", compose(5, f, g)); // 52

    use std::f64::consts::PI;
    enum Shape{
        Circle(f64), //radius or radii? plurals...
        Rectangle(f64,f64),
    }
    impl Shape{
        fn area(&self) -> f64 {
            match &self{
                Shape::Circle(r) => r*r*PI,
                Shape::Rectangle(l,w) => l*w,
            }
        }
    }
    //let circ: Shape = Shape::Circle(3.0);
    //println!("{:.2}", circ.area());
    //let rect: Shape = Shape::Rectangle(2.0,6.0);
    //println!("{:.2}", rect.area());
    use Shape::*;
    let c = Circle(3.0);
    println!("Circle area: {}", c.area()); // 28.274333882308138
    let r = Rectangle(6.0, 7.0);
    println!("Rectangle area: {}", r.area()); // 42

    fn f2n(f: fn(i32)->i32, mut n:u32, mut x:i32) -> i32 {
    // n is a copy intentionally,
    // x may or may not be a copy. &mut x if it is supposed to be a refrence.
        while n>0 {
            n-=1;
            x=f(x);
        }
        return x;
    }
    fn sq(x: i32) -> i32 {
        x * x
    }
    let x = 2;
    println!("{}", f2n(sq, 3, x));

    fn cycle (vector: &Vec<i32>, n: usize) -> Vec<i32>{
        let size = vector.len();
        let mut v: Vec<i32> = Vec::new();
        for i in n..size{
            v.push(vector[i]);
        }
        for j in 0..n{
            v.push(vector[j]);
        }
        return v;
    }
    let v = vec![1, 2, 3, 4, 5];
    println!("{:?}", cycle(&v, 2));
    println!("{:?}", v);

    /*
    [3, 4, 5, 1, 2]
    [1, 2, 3, 4, 5]
    */
}
