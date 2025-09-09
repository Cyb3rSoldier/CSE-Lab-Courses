<?php
// Class for Matrix Addition
class MatrixAdd {
    public function add($m1, $m2) {
        $result = [];
        for ($i = 0; $i < 2; $i++) {
            for ($j = 0; $j < 2; $j++) {
                $result[$i][$j] = $m1[$i][$j] + $m2[$i][$j];
            }
        }
        return $result;
    }
}

// Class for Matrix Subtraction
class MatrixSub {
    public function subtract($m1, $m2) {
        $result = [];
        for ($i = 0; $i < 2; $i++) {
            for ($j = 0; $j < 2; $j++) {
                $result[$i][$j] = $m1[$i][$j] - $m2[$i][$j];
            }
        }
        return $result;
    }
}

// Initialize variables
$output = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Matrix 1
    $m1 = [
        [$_POST['a11'], $_POST['a12']],
        [$_POST['a21'], $_POST['a22']]
    ];

    // Matrix 2
    $m2 = [
        [$_POST['b11'], $_POST['b12']],
        [$_POST['b21'], $_POST['b22']]
    ];

    // Decide operation
    if ($_POST['operation'] == "add") {
        $obj = new MatrixAdd();
        $output = $obj->add($m1, $m2);
    } elseif ($_POST['operation'] == "sub") {
        $obj = new MatrixSub();
        $output = $obj->subtract($m1, $m2);
    }


}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Matrix Operation</title>
</head>
<body>
    <h2>2×2 Matrix Addition and Subtraction</h2>
    <form method="POST">
        <h3>Matrix A</h3>
        <input type="number" name="a11" required>
        <input type="number" name="a12" required><br>
        <input type="number" name="a21" required>
        <input type="number" name="a22" required><br><br>

        <h3>Matrix B</h3>
        <input type="number" name="b11" required>
        <input type="number" name="b12" required><br>
        <input type="number" name="b21" required>
        <input type="number" name="b22" required><br><br>

        <button type="submit" name="operation" value="add">Add</button>
        <button type="submit" name="operation" value="sub">Subtract</button>
    </form>

    <?php
if (!empty($output)) {
    echo "<h3>Result:</h3>";
    for ($i = 0; $i < 2; $i++) {
        for ($j = 0; $j < 2; $j++) {
            echo $output[$i][$j] . " ";
        }
        echo "<br>";
    }
}
?>



</body>
</html>
