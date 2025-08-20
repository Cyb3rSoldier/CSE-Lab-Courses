<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Strong Number Check</title>
</head>
<body>
    <form action="strongNumber.php" method="POST">
        <label>Enter a Number: </label><br>
        <input type="number" name="number" required><br><br><br><br>
        <input type="submit" value="Submit"><br><br>
    </form>
</body>
</html>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $num = $_POST['number'];
    echo "Input Number: $num <br>";

    // Strong number check
    function factorial($n) {
        $fact = 1;
        for ($i = 1; $i <= $n; $i++) {
            $fact *= $i;
        }
        return $fact;
    }

    $temp = $num;
    $sum = 0;
    while ($temp > 0) {
        $digit = $temp % 10;
        $sum += factorial($digit);
        $temp = (int)($temp / 10);
    }

    if ($sum == $num) {
        echo "$num is a Strong Number ✅";
    } else {
        echo "$num is NOT a Strong Number ❌";
    }
}
?>
