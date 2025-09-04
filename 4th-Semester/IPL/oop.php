<?php
// Initialize values
$num1 = $num2 = $result = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $num1 = $_POST['num1'];
    $num2 = $_POST['num2'];
    $res = $_POST['res'];

    class Oop
    {
        function add($num1, $num2)
        {
            return $num1 + $num2;
        }
        function sub($num1, $num2)
        {
            return $num1 - $num2;
        }
        function mul($num1, $num2)
        {
            return $num1 * $num2;
        }
        function div($num1, $num2)
        {
            if ($num2 == 0) {
                return "Error: Division by zero";
            }
            return $num1 / $num2;
        }
    }

    $obj = new Oop();

    if ($res == "add") {
        $result = $obj->add($num1, $num2);
    } elseif ($res == "sub") {
        $result = $obj->sub($num1, $num2);
    } elseif ($res == "mul") {
        $result = $obj->mul($num1, $num2);
    } elseif ($res == "div") {
        $result = $obj->div($num1, $num2);
    }
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>OOP Calculator</title>
</head>

<body>
    <h3>Calculator!</h3>
    <form action="oop.php" method="post">
        <input type="number" placeholder="Enter Number 1" name="num1" value="<?php echo $num1; ?>"><br><br>
        <input type="number" placeholder="Enter Number 2" name="num2" value="<?php echo $num2; ?>"><br><br>
        <input type="text" placeholder="Output: " name="output" readonly value="<?php echo $result; ?>"><br><br>

        <button type="submit" name="res" value="add">Add</button>
        <button type="submit" name="res" value="sub">Sub</button>
        <button type="submit" name="res" value="mul">Mul</button>
        <button type="submit" name="res" value="div">Div</button>
    </form>
</body>

</html>
