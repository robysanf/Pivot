var server = "ws://192.168.1.90:8080/";	
var ArrayVar = null;
var last_response ="";
var conf=1;

document.addEventListener('deviceready', function () {
    
var ws = new WebSocket(server);
document.getElementById("appwdd").style.visibility='hidden';
document.getElementById("slideshow").style.visibility='hidden';
document.getElementById("setup").style.visibility='hidden';
document.getElementById("gridContainer").style.visibility='hidden';

    ws.onopen = function () {
        console.log('open');
        this.send('init');         // transmit "init" after connecting
    };

    ws.onmessage = function (event) {
        console.log(event.data); 
		 last_response=event.data;
		 document.getElementById("websocket").innerHTML += "<- " + last_response + "\n";
		 conf=getVar("CONFIGURAZIONE");
		 if(conf==1)
		 { 
	       makeConfigHtml(last_response);
		   document.getElementById("page1").style.visibility='hidden';
		   document.getElementById("setup").style.visibility='visible';
		   document.getElementById("gridContainer").style.visibility='visible';
		 }else if(conf==0){
			document.getElementById("page1").style.visibility='visible';
			document.getElementById("setup").style.visibility='hidden';
			document.getElementById("appwdd").style.visibility='hidden';
			makeConfigHtml(last_response);			
		 }else{
			 document.getElementById("message").innerHTML="Nessuna Configurazione ricevuta dal dispositivo";
		 }
        this.close();
    };

    ws.onerror = function () {
        console.log('error occurred!');
    };

    ws.onclose = function (event) {
        console.log('close code=' + event.code);
    };
}, false);

function makeConfigHtml(rec){
    
	
	if(rec.indexOf("#")==-1){
	  document.getElementById("txt_com").style.visibility='visible';
	  document.getElementById("txt_com").innerHTML="Nessuna Configurazione ricevuta dal dispositivo";
	}else{
	  removeAllChildNodes(document.getElementById("gridContainer"))
	ArrayVar=rec.split("#");
	for(i=0;i<ArrayVar.length;i++){
	
		myArray=ArrayVar[i].split("=");
		nome_var=""+myArray[0];
		valore_var=" "+myArray[1];
				
		obj_input = document.createElement("div");
		obj_input.className ="grid-item";
		obj_input.id=""+i;
		document.getElementById("gridContainer").appendChild(obj_input);		

		var label_x = document.createElement("P");
		var t = document.createTextNode(nome_var);
		label_x.className ="textsize";
		label_x.appendChild(t);
		obj_input.appendChild(label_x);	

		obj_input = document.createElement("div");
		obj_input.className ="grid-item";
		obj_input.id="f"+i;
		document.getElementById("gridContainer").appendChild(obj_input);

		var x = document.createElement("INPUT");
		x.setAttribute("type", "text");
		x.setAttribute("id", nome_var);
		x.setAttribute("value", valore_var);
		obj_input.appendChild(x);

	  }
	}
}

function send(a) {
	firstsocket = new WebSocket(server);
	document.getElementById("connection").innerHTML = '<p style="color:#00A45B;"><svg fill="none" version="1.1" width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path d="m12 17.435c-0.9281 0-1.68 0.7548-1.68 1.6811 0 0.9262 0.7519 1.6776 1.68 1.6776 0.9274 0 1.68-0.7514 1.68-1.6776 0-0.9263-0.7526-1.6811-1.68-1.6811zm11.744-7.9502c-2.9324-3.4845-7.2128-5.4847-11.743-5.4847-4.5306 0-8.8119 2.0002-11.744 5.4847-0.38904 0.46375-0.32785 1.1548 0.13607 1.5437 0.20274 0.1716 0.45297 0.2565 0.70228 0.2565 0.31416 0 0.62466-0.1315 0.83836-0.388 2.5151-2.9924 6.1827-4.7078 10.068-4.7078 3.8813 0 7.5516 1.7153 10.067 4.7042 0.2137 0.2601 0.5242 0.3916 0.8384 0.3916 0.2493 0 0.4995-0.0849 0.7032-0.2565 0.463-0.3889 0.5242-1.08 0.1351-1.5437zm-11.743-1.1019c-3.2356 0-6.2932 1.4259-8.3872 3.9154-0.38904 0.4638-0.33151 1.1548 0.13242 1.5437 0.20639 0.1716 0.45662 0.2565 0.70594 0.2565 0.3105 0 0.62101-0.1314 0.83836-0.3879 1.6767-1.9938 4.1206-3.1386 6.7105-3.1386 2.59 0 5.0329 1.1448 6.7096 3.1386 0.2183 0.2565 0.5279 0.3879 0.8384 0.3879 0.2502 0 0.4995-0.0812 0.7068-0.2565 0.464-0.3889 0.5242-1.0799 0.1315-1.5437-2.094-2.4894-5.1507-3.9154-8.3863-3.9154zm0 4.3828c-1.9443 0-3.7781 0.8554-5.0338 2.3498-0.38904 0.4601-0.32785 1.1512 0.13516 1.5401 0.20366 0.1752 0.45297 0.2574 0.7032 0.2574 0.31416 0 0.62375-0.1324 0.84201-0.3889 0.83471-0.9987 2.0584-1.5693 3.3534-1.5693s2.5178 0.5706 3.3525 1.5693c0.2183 0.2565 0.5288 0.3889 0.842 0.3889 0.2503 0 0.4996-0.0822 0.7032-0.2574 0.464-0.3889 0.5242-1.08 0.1352-1.5401-1.2557-1.4944-3.0886-2.3498-5.0329-2.3498z" clip-rule="evenodd" fill="#00A45B" fill-rule="evenodd"/></svg> Connected</p>';

	firstsocket.onopen = function() {
	
	firstsocket.send(a);
	console.log("invio "+a);
 }
  firstsocket.onmessage = function(m) {
   

    messageTime = Date.now();
    setTimeout(function() {
      if (Date.now() - messageTime > 1000 && !called) {
        called = true;
        document.getElementById("connection").innerHTML = '<p style="color:#F75535;"><svg fill="none" version="1.1" width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path d="m12 17.435c-0.9281 0-1.68 0.7548-1.68 1.6811 0 0.9262 0.7519 1.6776 1.68 1.6776 0.9274 0 1.68-0.7514 1.68-1.6776 0-0.9263-0.7526-1.6811-1.68-1.6811zm11.744-7.9502c-2.9324-3.4845-7.2128-5.4847-11.743-5.4847-4.5306 0-8.8119 2.0002-11.744 5.4847-0.38904 0.46375-0.32785 1.1548 0.13607 1.5437 0.20274 0.1716 0.45297 0.2565 0.70228 0.2565 0.31416 0 0.62466-0.1315 0.83836-0.388 2.5151-2.9924 6.1827-4.7078 10.068-4.7078 3.8813 0 7.5516 1.7153 10.067 4.7042 0.2137 0.2601 0.5242 0.3916 0.8384 0.3916 0.2493 0 0.4995-0.0849 0.7032-0.2565 0.463-0.3889 0.5242-1.08 0.1351-1.5437zm-11.743-1.1019c-3.2356 0-6.2932 1.4259-8.3872 3.9154-0.38904 0.4638-0.33151 1.1548 0.13242 1.5437 0.20639 0.1716 0.45662 0.2565 0.70594 0.2565 0.3105 0 0.62101-0.1314 0.83836-0.3879 1.6767-1.9938 4.1206-3.1386 6.7105-3.1386 2.59 0 5.0329 1.1448 6.7096 3.1386 0.2183 0.2565 0.5279 0.3879 0.8384 0.3879 0.2502 0 0.4995-0.0812 0.7068-0.2565 0.464-0.3889 0.5242-1.0799 0.1315-1.5437-2.094-2.4894-5.1507-3.9154-8.3863-3.9154zm0 4.3828c-1.9443 0-3.7781 0.8554-5.0338 2.3498-0.38904 0.4601-0.32785 1.1512 0.13516 1.5401 0.20366 0.1752 0.45297 0.2574 0.7032 0.2574 0.31416 0 0.62375-0.1324 0.84201-0.3889 0.83471-0.9987 2.0584-1.5693 3.3534-1.5693s2.5178 0.5706 3.3525 1.5693c0.2183 0.2565 0.5288 0.3889 0.842 0.3889 0.2503 0 0.4996-0.0822 0.7032-0.2574 0.464-0.3889 0.5242-1.08 0.1352-1.5401-1.2557-1.4944-3.0886-2.3498-5.0329-2.3498z" clip-rule="evenodd" fill="#F75535" fill-rule="evenodd"/></svg> Disconnected</p>';
        socket.close();
      }
    }, 2000);
    document.getElementById("websocket").innerHTML += "<- " + m.data + "\n";
	last_response=m.data;
	}
	
    firstsocket.onclose = function() {
    document.getElementById("connection").innerHTML = '<p style="color:#F75535;"><svg fill="none" version="1.1" width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path d="m12 17.435c-0.9281 0-1.68 0.7548-1.68 1.6811 0 0.9262 0.7519 1.6776 1.68 1.6776 0.9274 0 1.68-0.7514 1.68-1.6776 0-0.9263-0.7526-1.6811-1.68-1.6811zm11.744-7.9502c-2.9324-3.4845-7.2128-5.4847-11.743-5.4847-4.5306 0-8.8119 2.0002-11.744 5.4847-0.38904 0.46375-0.32785 1.1548 0.13607 1.5437 0.20274 0.1716 0.45297 0.2565 0.70228 0.2565 0.31416 0 0.62466-0.1315 0.83836-0.388 2.5151-2.9924 6.1827-4.7078 10.068-4.7078 3.8813 0 7.5516 1.7153 10.067 4.7042 0.2137 0.2601 0.5242 0.3916 0.8384 0.3916 0.2493 0 0.4995-0.0849 0.7032-0.2565 0.463-0.3889 0.5242-1.08 0.1351-1.5437zm-11.743-1.1019c-3.2356 0-6.2932 1.4259-8.3872 3.9154-0.38904 0.4638-0.33151 1.1548 0.13242 1.5437 0.20639 0.1716 0.45662 0.2565 0.70594 0.2565 0.3105 0 0.62101-0.1314 0.83836-0.3879 1.6767-1.9938 4.1206-3.1386 6.7105-3.1386 2.59 0 5.0329 1.1448 6.7096 3.1386 0.2183 0.2565 0.5279 0.3879 0.8384 0.3879 0.2502 0 0.4995-0.0812 0.7068-0.2565 0.464-0.3889 0.5242-1.0799 0.1315-1.5437-2.094-2.4894-5.1507-3.9154-8.3863-3.9154zm0 4.3828c-1.9443 0-3.7781 0.8554-5.0338 2.3498-0.38904 0.4601-0.32785 1.1512 0.13516 1.5401 0.20366 0.1752 0.45297 0.2574 0.7032 0.2574 0.31416 0 0.62375-0.1324 0.84201-0.3889 0.83471-0.9987 2.0584-1.5693 3.3534-1.5693s2.5178 0.5706 3.3525 1.5693c0.2183 0.2565 0.5288 0.3889 0.842 0.3889 0.2503 0 0.4996-0.0822 0.7032-0.2574 0.464-0.3889 0.5242-1.08 0.1352-1.5401-1.2557-1.4944-3.0886-2.3498-5.0329-2.3498z" clip-rule="evenodd" fill="#F75535" fill-rule="evenodd"/></svg> Disconnected</p>';
    
  }
 
}
function makeResponseToSave() {

     resp="save";
	 for(i=0;i<ArrayVar.length;i++){
	
		myArray=ArrayVar[i].split("=");
		nome_var=""+myArray[0];
		item=document.getElementById(nome_var);				
		resp=resp+item.id+"="+item.value+"#";		
	  }
   return resp;
}

function getVar(nome_var){
	//prima devo valorizzare ArrayVar chiamando il device remote
	if(last_response == undefined || last_response == null || last_response.length<1){
		return "";
	}
	ArrayVar=last_response.split("#");
	for(i=0;i<ArrayVar.length;i++){
	
		myArray=ArrayVar[i].split("=");
		item=""+myArray[0];
		valore_var=" "+myArray[1];
		if(item == nome_var)
		{
	     return valore_var;
	  }
	}
	return "";
}
