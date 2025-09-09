<?php

$output = '';

if ($_SERVER["REQUEST_METHOD"] == 'POST') {
    $num1 = $_POST['num1'];
    $num2 = $_POST['num2'];
    $result = $_POST['submit'];

    function orGate($num1, $num2) {
        if ($num1 == 0 && $num2 == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    function andGate($num1, $num2) {
        if ($num1 == 1 && $num2 == 1) {
            return 1;
        } else {
            return 0;
        }
    }

    if ($result == 'or') {
        $output = orGate($num1, $num2);
    }
    if ($result == 'and') {
        $output = andGate($num1, $num2);
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Logic Gate</title>
</head>
<body>
    <form action="" method="POST">
        <input type="number" name="num1" placeholder="Enter number 1" value="<?php echo $num1; ?>" required><br><br>
        <input type="number" name="num2" placeholder="Enter number 2" value="<?php echo $num2; ?>" required><br><br>

        <button type="submit" name="submit" value="or">OR</button>
        <button type="submit" name="submit" value="and">AND</button>
        <br><br>

        <input type="number" placeholder="Output" readonly value="<?php echo $output; ?>">
    </form>
</body>
</html>
