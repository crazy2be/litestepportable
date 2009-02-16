// Global Variables
var PageNumber = 1; //The tutorial page we are on
var MaxPages = 4; //The number of pages in the turorial

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
	PageNumber=1;
	GotoPage();
}

function GotoPage() {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	xmlHttpReq.open("GET", "Page" + PageNumber + ".html", false);
	xmlHttpReq.send();
	//alert(xmlHttpReq.responseText);
	ContentDiv.innerHTML = xmlHttpReq.responseText;
}