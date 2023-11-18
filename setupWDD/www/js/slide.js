
//********************* SLIDE  
let slideIndex = 1;
//showSlides(slideIndex);  parte con onload

function plusSlides(n) {
  showSlides(slideIndex += n);
  document.getElementById("message").innerHTML = "";
}

function currentSlide(n) {
  showSlides(slideIndex = n);
  document.getElementById("message").innerHTML = "";
}

function showSlides(n) {
  let i;
  let slides = document.getElementsByClassName("mySlides");
 
  if (n > slides.length) {slideIndex = 1}    
  if (n < 1) {slideIndex = slides.length}
  for (i = 0; i < slides.length; i++) {
    slides[i].style.display = "none";  
	slides[slideIndex-1].style.visibility = 'hidden';
  }
  
  slides[slideIndex-1].style.display = "block"; 
  slides[slideIndex-1].style.visibility = 'visible';
  //dots[slideIndex-1].className += " active";
  var txt_com = document.getElementById("message");
	txt_com.addEventListener('click',()=>{
	document.getElementById("page1").style.visibility='hidden';
	document.getElementById("setup").style.visibility='visible';
	document.getElementById("gridContainer").style.visibility='visible';
})
}

function inizia() {
  send("iniz");
  plusSlides(1);
}

function calcola_encoder() {
  send("enco");
  plusSlides(1);
}

function imposta_pos_zero() {
  send("pos0");
  plusSlides(1);
}

function imposta_pos_aperto() {
	
  send("posA");
  plusSlides(1);
}

function calcola_imp() {
	raggio=document.getElementById("fraggio").value;
	if(validateNum(raggio))
	{
      send("impu"+raggio);
      plusSlides(1);
	}
}

function move() {
  send("move");
 
}

function chiude() {
  send("moto-");
  plusSlides(1);
}

function apre() {
  send("moto");
  plusSlides(1);
}

function cons() {
	document.getElementById("fraggio").value;
  send("cons");
  plusSlides(1);
}

function velo() {
  send("velo");
  plusSlides(1);
}

function save(a) {
	if(a==1)
	   document.getElementById("CONFIGURAZIONE").value='1';
	send(makeResponseToSave());
     
}

function apri() {
  send("apri");
 
}

function chiudi() {
  send("chiu");
 
}

function set() {
	makeConfigHtml(last_response);
  document.getElementById("page8").style.visibility='hidden';
	document.getElementById("setup").style.visibility='visible';
	document.getElementById("gridContainer").style.visibility='visible';
 
}

function validateNum(x) {
  let text;
  if (isNaN(x) || x < 1 || x > 10000) {
    text = "Input not valid";
	document.getElementById("message").innerHTML = text;
    return false;
  } else {
	  document.getElementById("message").innerHTML = "";
    return true;
  }
  
}
function removeAllChildNodes(parent) {
    while (parent.firstChild) {
        parent.removeChild(parent.firstChild);
    }
}
	