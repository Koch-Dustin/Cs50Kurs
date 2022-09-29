
menu1_is_open = false;
menu2_is_open = false;
menu3_is_open = false;

function open_on_click(number) {
    num = number;
    if (menu1_is_open) {
        if (number == 1) {
            document.getElementById("projekt_one_arrow").src = "img/Arrow_Right.png";
            document.getElementById("projekt_one_container").style.display = "none";
            menu1_is_open = false;
        }
    } else {
        if (number == 1) {
            document.getElementById("projekt_one_arrow").src = "img/Arrow_Down.png";
            document.getElementById("projekt_one_container").style.display = "block";
            menu1_is_open = true;
        }
    }

    if (menu2_is_open) {
        if (number == 2) {
            document.getElementById("projekt_two_arrow").src = "img/Arrow_Right.png";
            document.getElementById("projekt_two_container").style.display = "none";
            menu2_is_open = false;
        }
    } else {
        if (number == 2) {
            document.getElementById("projekt_two_arrow").src = "img/Arrow_Down.png";
            document.getElementById("projekt_two_container").style.display = "block";
            menu2_is_open = true;
        }
    }

    if (menu3_is_open) {
        if (number == 3) {
            document.getElementById("projekt_three_arrow").src = "img/Arrow_Right.png";
            document.getElementById("projekt_three_container").style.display = "none";
            menu3_is_open = false;
        }
    } else {
        if (number == 3) {
            document.getElementById("projekt_three_arrow").src = "img/Arrow_Down.png";
            document.getElementById("projekt_three_container").style.display = "block";
            menu3_is_open = true;
        }
    }

}
