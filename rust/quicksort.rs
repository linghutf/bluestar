extern crate std as core;
//extern crate rand;

use core::cmp::Ordering;
//use rand::Rng;

fn partition<T>(arr:&mut [T],left:isize,right:isize,cmp:&Fn(&T,&T)->Ordering)
    -> isize
{
    if right <= left{
        return -1;
    }
    unsafe{
    let val:*mut T = &mut arr[right as usize];
    let mut k:isize = left;
    for i in left..right{
        if cmp(&arr[i as usize],&*val)==Ordering::Less{
            if i!=k{
                arr.swap(i as usize,k as usize);
            }
            k = k+1;
        }
    }
    arr.swap(k as usize,right as usize);
    return k;
    }
}

fn quicksort<T,F>(arr:&mut [T],left:isize,right:isize,cmp:&Fn(&T,&T) -> Ordering){
    if left<right{
        let pivot:isize = partition(arr,left,right,&cmp);
        quicksort(arr,left,pivot-1,&cmp);
        quicksort(arr,pivot+1,right,&cmp);
    }
}

pub fn qsort<T,F>(arr:&mut [T],cmp:&Fn(&T,&T) -> Ordering){
    if arr.len()<=1{
        return
    }
    let right:usize = arr.len()-1;
    quicksort(arr,0,right as isize,&cmp);
}


pub fn main() {
    //let mut rng = rand::rng();
    //let len:usize = rng.gen();
    //let mut v:Vec<isize> = rng.gen_iter::<isize>().take(len%100+1).collect();
    let mut v = [-3,2,1,4,3];
    qsort(&mut v,|a,b| a.cmp(b));
    //partition(&mut v,0,5,|a,b| a.cmp(b));
}
