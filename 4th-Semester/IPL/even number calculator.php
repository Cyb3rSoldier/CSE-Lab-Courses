<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Even Number Calculator</title>
</head>

<body>
    <form action="even number calculator.php" method="post">
        <label>Num1: </label>
        <input type="number" name="num1" required><br><br>
        <label>Num2: </label>
        <input type="number" name="num2" required><br><br>
        <input type="submit"><br><br>
    </form>
</body>

</html>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $num1 = $_POST['num1'];
    $num2 = $_POST['num2'];
    echo "Inputed Numbers: $num1 and $num2" . "<br>";
    if ($num1 % 2 != 0) {
        $num1 = $num1 * 2;
    }
    if ($num2 % 2 != 0) {
        $num2 = $num2 * 2;
    }
    $sum = $num1 + $num2;
    $sub = $num1 - $num2;
    echo "Add: $sum" . " " . "Sub: $sub";
}
?>