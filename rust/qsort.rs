
fn partition(a:&mut [i32],left:usize,right:usize)-> usize{
    let mut k = left;
    let val = a[right];

    for i in left..right {
        if a[i] < val {
            if i != k {
                a.swap(i,k);
            }
            k+=1;
        }
    }
    a.swap(k,right);
    return k;
}

fn quicksort(a:&mut [i32],left:usize,right:usize){
    if left<right{
        let pivot = partition(a,left,right);
        quicksort(a,left,pivot-1);
        quicksort(a,pivot+1,right);
    }
}

fn qsort(a:&mut [i32]){
    if a.len()<=1{
        return
    }
    let right = a.len()-1;
    quicksort(a,0,right);
}

pub fn main() {
    let mut arr = [-3,1,2,4,3];
    println!("before:");
    for i in arr.iter(){
        print!("{}\t",i);
    }

    qsort(&mut arr);
    println!("\nafter:");
    for i in arr.iter(){
        print!("{}\t",i);
    }
    println!("");
}
