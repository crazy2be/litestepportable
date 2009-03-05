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
		GotoTutorialPage();
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
		GotoTutorialPage();
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
	GotoTutorialPage();
	if (PageNumber < MaxPages) {
		CancelButton.style.display = "inline";
		NextButton.src = "..\\img\\Next.png";
	}
}

function GotoTutorialPage() {
	GotoPage("..\\" + Lang + "\\html\\Page" + PageNumber + ".html");
}

function GotoPage(Path) {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		ContentDiv.innerHTML = ParseForCode(xmlHttpReq.responseText);
	} catch (error) {
		alert('Error occured while attempting to retreive page:\n'
			+ '(' + Path + ')\n'
			+ error.message + '\n');
	}
	// Find all the images in the loaded document, and correct their paths.
	var Images = ContentDiv.getElementsByTagName('img');
	for (i = 0; i < Images.length; i++) {
		var Image = Images[i].src;
		var FileName = Image.substring(
			Image.lastIndexOf('/')+1);
		var Path = Image.substring(
			0, Image.lastIndexOf('/'));
		Path = Path.substring(
			0, Path.lastIndexOf('/')+1);
		//alert(Path);
		Images[i].src = Path
			+ Lang + '/img/' + FileName;
		//alert(Images[i]);
	}
	/*var Codes = getElementsByClass('Code', ContentDiv, 'Div');
	for (i = 0; i < Codes.length; i++) {
		var Code = Codes[i].innerHTML;
		var LastLineFeed = Code.lastIndexOf('\n');
		for (j = 0; j < LastLineFeed; j = Code.indexOf('\n')) {
			
		}
	}*/
	//alert(xmlHttpReq.responseText);
}

function ChangeLang() {
	Lang = LangSelector.value;
	/*BegginingButton.src = "..\\img\\Beggining.png";
	BackButton.src = "..\\img\\Back.png";
	NextButton.src = "..\\img\\Next.png";
	CancelButton.src = "..\\img\\Cancel.png";*/
	GotoTutorialPage();
}

function ToggleTutorialSelectorFunc() {
	//Toggler = TutorialSelectorDiv.style.display;
	TutorialSelectorDiv.style.display = 
		(TutorialSelectorDiv.style.display == "none")
			? ("block") : ("none");
	ContentDiv.style.width =
		(ContentDiv.style.width == "581px")
			? ("481px") : ("581px");
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

function ParseForCode(ToParse) {
	EndLines = '';
	Lines = new Array();
	Lines = ToParse.split('\n');
	CodeLinePattern = new RegExp('<div(\\s+)class="(\\s*)code(\\s*)"(.*?)>');
	EndCodeBlock = new RegExp('</div>');
	InCodeDiv = false;
	for (i = 1; i < Lines.length; i++) {
		EndLines += Lines[i];
		EndLines += '\n';
		if (InCodeDiv) {
			if (EndCodeBlock.test(Lines[i])) {
				InCodeDiv = false;
			} else {
				EndLines += '<BR />';
			}
		}
	    if (CodeLinePattern.test(Lines[i])) {
			InCodeDiv = true;
			//alert(Lines[i] + '\nMatched!');
		}
	}
	return EndLines;
}

function getElementsByClass(searchClass,node,tag) {
	var classElements = new Array();
	if ( node == null )
		node = document;
	if ( tag == null )
		tag = '*';
	var els = node.getElementsByTagName(tag);
	var elsLen = els.length;
	var pattern = new RegExp("(^|\\s)"+searchClass+"(\\s|$)");
	for (i = 0, j = 0; i < elsLen; i++) {
		if ( pattern.test(els[i].className) ) {
			classElements[j] = els[i];
			j++;
		}
	}
	return classElements;
}