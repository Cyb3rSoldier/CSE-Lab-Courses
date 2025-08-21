<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sequence Number 2</title>
</head>

<body>
    <form action="sequence number 2.php" method="post">
        <label>Enter the number: </label><br>
        <input type="number" name="num" required><br><br>
        <input type="submit"><br><br>
    </form>
</body>

</html>

<?php
if($_SERVER["REQUEST_METHOD"]=="POST"){
    $num = $_POST['num'];
    $mul = 1;
    echo "Inputed value: $num"."<br>";
    for($i= 1; $i<=$num; $i++){
        $mul = $i * $i;
        echo $mul." ";
    }
}
?>