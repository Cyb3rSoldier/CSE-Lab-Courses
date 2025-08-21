<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Strong Number Check</title>
</head>
<body>
    <form action="strongNumber.php" method="post">
        <label>Enter a Number: </label><br>
        <input type="number" name="number" required><br><br>
        <input type="submit" name="submit"><br><br>
    </form>
</body>
</html>

<?php
if($_SERVER["REQUEST_METHOD"]=="POST"){
    echo "Output: <br>";
    $num = $_POST['number'];
    function factorial($n){
        $fact = 1;
        for($i=1; $i<=$n; $i++){
            $fact= $fact*$i;
        }
        return $fact;
    }
    $temp = $num;
    $sum = 0;
    while($temp>0){
        $digit = $temp%10;
        $sum = $sum + factorial($digit);
        $temp = (int)($temp/10);
    }
    if($sum == $num){
        echo "$num is a Strong Number!";
    }
    else{
        echo "$num is not a Strong Number!";
    }
}
?>