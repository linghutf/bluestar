pub fn main() {
    let msg = "中国,长城";
    for i in msg.chars(){
        println!("{}",i);
    }
    let c = msg.chars().nth(1);
    /*if c == ' '{
        println!("OK");
    }*/
}
