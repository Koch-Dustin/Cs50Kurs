menu1_is_open = false;
menu2_is_open = false;
menu3_is_open = false;

function open_on_click(number) {
  num = number;
  const arrow1 = document.getElementById("projekt_one_arrow");
  if (menu1_is_open) {
    if (number == 1) {
      arrow1.src = "img/Arrow_Right.png"
      document.getElementById("projekt_one_container").style.display = "none";
      menu1_is_open = false;
    }
  } else {
    if (number == 1) {
      arrow1.src = "img/Arrow_Down.png"
      document.getElementById("projekt_one_container").style.display = "block";
      menu1_is_open = true;
    }
  }

  const arrow2 = document.getElementById("projekt_two_arrow");
  if (menu2_is_open) {
    if (number == 2) {
      arrow2.src = "img/Arrow_Right.png";
      document.getElementById("projekt_two_container").style.display = "none";
      menu2_is_open = false;
    }
  } else {
    if (number == 2) {
      arrow2.src = "img/Arrow_Down.png";
      document.getElementById("projekt_two_container").style.display = "block";
      menu2_is_open = true;
    }
  }

  const arrow3 = document.getElementById("projekt_three_arrow");
  if (menu3_is_open) {
    if (number == 3) {
      arrow3.src = "img/Arrow_Right.png";
      document.getElementById("projekt_three_container").style.display = "none";
      menu3_is_open = false;
    }
  } else {
    if (number == 3) {
      arrow3.src = "img/Arrow_Down.png";;
      document.getElementById("projekt_three_container").style.display =
        "block";
      menu3_is_open = true;
    }
  }
}
