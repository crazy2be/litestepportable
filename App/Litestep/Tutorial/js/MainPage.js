// Global Variables
var PageNumber = 1; //The tutorial page we are on
var MaxPages = 4; //The number of pages in the turorial
var Lang = "Eng"; // The language

// Handlers
//window.onerror=handleErr;

function ExitCode() {
	if (confirm("Are you sure you wish to exit?\n"
		+ "This tutorial covers only the basics, and will likely reduce frustration later...\n"
		+ "The tutorial will be run the next time you start litestep.")) {
			window.close();
	}
}

function NextPage() {
	if (PageNumber < MaxPages) {
		PageNumber++;
		GotoPage();
		if (PageNumber == MaxPages) {
			CancelButton.style.display = "none";
			NextButton.src = "..\\img\\Finish.png";
		}
	} else if (PageNumber == MaxPages) {
		window.close();
	}
}

function PrevPage() {
	PageNumber--;
	if (PageNumber > 1) {
		GotoPage();
	} else {
		FirstPage();
	}
	if (PageNumber < MaxPages) {
		CancelButton.style.display = "inline";
		NextButton.src = "..\\img\\Next.png";
	}
}

function FirstPage() {
	//ToggleTutorialSelector()
	PageNumber=1;
	GotoPage();
	if (PageNumber < MaxPages) {
		CancelButton.style.display = "inline";
		NextButton.src = "..\\img\\Next.png";
	}
}

function GotoPage() {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	xmlHttpReq.open("GET", "..\\" + Lang + "\\html\\Page" + PageNumber + ".html", false);
	try {
		xmlHttpReq.send();
		ContentDiv.innerHTML = xmlHttpReq.responseText;
	} catch (error) {
		alert('Error occured while attempting to retreive page:\n'
			+ error.message + '\n');
	}
	//alert(xmlHttpReq.responseText);
}

function ChangeLang() {
	Lang = LangSelector.value;
	/*BegginingButton.src = "..\\img\\Beggining.png";
	BackButton.src = "..\\img\\Back.png";
	NextButton.src = "..\\img\\Next.png";
	CancelButton.src = "..\\img\\Cancel.png";*/
	GotoPage();
}

function ToggleTutorialSelectorFunc() {
	//Toggler = TutorialSelectorDiv.style.display;
	TutorialSelectorDiv.style.display = 
		(TutorialSelectorDiv.style.display == "none")
			? ("block") : ("none");
	ContentDiv.style.width =
		(ContentDiv.style.width == "580px")
			? ("480px") : ("580px");
	ContentDiv.style.left =
		(ContentDiv.style.left == "10px")
			? ("110px") : ("10px");
	ToggleTutorialSelector.style.left =
		(ToggleTutorialSelector.style.left == "0px")
			? ("100px") : ("0px");
}
/*function handleErr(msg, url, l) {
	alert('SOMETHING WENT WRONG');
	alert('Something whent wrong :(\n'
		+ msg
		+ '\nline: ' + url
		+ '\npage: ' + l);
	return false;
}*/