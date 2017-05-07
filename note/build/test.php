<?php
$arr = Array(12,34);
echo empty($arr);
for($i=0;$i<count($arr);++$i)
{
    echo $arr[$i];
}

function unix_to_dt($unix)
{
    $ret='';
    if($unix!=0){
        $ret=date('Y-m-d',$unix);
    }
    return $ret;
}

echo 'dt:'.unix_to_dt(1440)."\n";
?>
