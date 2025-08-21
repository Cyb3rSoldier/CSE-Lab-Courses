<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Form</title>
</head>
<body>
    <form action="form.php" method="post">
        <label>Name: </label><br>
        <input type="text" name="name"><br><br>
        <label>ID: </label><br>
        <input type="number" name="id"><br><br>
        <label>Phone Number: </label><br>
        <input type="number" name="number"><br><br>
        <label>Gender: </label>
        <input type="radio" value="male" name="gender">Male
        <input type="radio" value="female" name="gender">Female
        <br><br>
        <label>Blood Group: </label>
        <select name="blood">
            <option value="O+">O+</option>
            <option value="O-">O-</option>
            <option value="A+">A+</option>
            <option value="A-">A-</option>
            <option value="AB+">AB+</option>
            <option value="AB-">AB-</option>
            <option value="B+">B+</option>
            <option value="B-">B-</option>
        </select>
        <br><br>
        <input type="submit">
    </form>
    <br><br><br>
</body>
</html>

<?php
if($_SERVER["REQUEST_METHOD"]=="POST"){
$name = $_POST['name'];
$id = $_POST['id'];
$num = $_POST['number'];
$gender = $_POST['gender'];
$blood = $_POST['blood'];
echo "Name: $name"."<br>";
echo "Name: $id"."<br>";
echo "Name: $num"."<br>";
echo "Name: $gender"."<br>";
echo "Name: $blood"."<br>";
}
?>