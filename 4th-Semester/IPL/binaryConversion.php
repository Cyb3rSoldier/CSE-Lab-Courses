<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <form action="binaryConversion.php" method="post">
        <input type="number" name="decimal" placeholder="Enter decimal value"><br><br>
        <button type="submit">submit</button><br><br>
    </form>
</body>

</html>

<?php
if ($_SERVER["REQUEST_METHOD"]  == "POST") {
    $decimal = $_POST['decimal'];

    if ($decimal == 0) {
        echo "Binary: 0";
    } else {
        $i = 0;
        $binary = [];
        while ($decimal > 0) {
            $binary[$i] = $decimal % 2;
            $decimal = intdiv($decimal,2);
            $i++;
        }

        echo "Binary: ";
        for ($j = $i - 1; $j >= 0; $j--) {
            echo $binary[$j];

        }
    }
}

?>