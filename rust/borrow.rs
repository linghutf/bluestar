fn swap(a:&mut i32,b:&mut i32){
    let c = *a;
    *a = *b;
    *b = c;
}

fn square(arr:&mut[i32]){
    for idx in arr{
        //arr[idx]*=arr[idx];
        *idx=(*idx)*(*idx);
    }
}

/*fn square_vec(arr:&mut Vec<isize>){
    for idx in arr{
        //arr[idx]*=arr[idx];
        *idx=(*idx)*(*idx);
    }
}*/
pub fn main() {
    let mut a = 10;
    let mut b = 12;
    println!("a={},b={}",a,b);
    swap(&mut a,&mut b);
    println!("a={},b={}",a,b);

    // 针对数组
    let mut v = [1,2,3];
    v[0]=4;
    println!("before:");
    for i in v.iter(){
        println!("{}",i);
    }
    square(&mut v);
    println!("after:");
    for i in v.iter(){
        println!("{}",i);
    }
}
