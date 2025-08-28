<?php
function add($a, $b) {
    return $a + $b;
}

$result = '';
if ($_SERVER['REQUEST_METHOD'] == 'POST' && $_POST['res'] == 'add') {
    $num1 = $_POST['num1'];
    $num2 = $_POST['num2'];
    $result = add($num1, $num2);
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Sum of Two Numbers</title>
</head>
<body>

<form method="post">
    <input type="number" name="num1" placeholder="Enter first number"><br><br>
    <input type="number" name="num2" placeholder="Enter second number"><br><br>
    <button type="submit" name="res" value="add">Add</button>
</form>

<p>Result: <?= $result ?></p>

</body>
</html>