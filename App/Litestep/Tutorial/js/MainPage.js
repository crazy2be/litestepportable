// Global Variables
var PageNumber = 1; //The tutorial page we are on
var MaxPages = 4; //The number of pages in the turorial
var Lang = "Eng"; // The language
var Them = "Default"; //The theme
var CurTut = "LiteStepPortable Introduction"; //The Tutorial name

// Handlers
//window.onerror=handleErr;
function LoadingCode() {
	//document.getElementsByTagName('body')[0]
	//	.style.behavior = 'url(\'..\\css\\WH3.htc\')'
	FirstPage();
	LoadIndex();
	LoadLangs();
	LoadThemes();
	LoadTuts();
	LoadTheme();
}

function LoadIndex() {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		Path = '..\\Lang\\' + Lang + '\\' + CurTut + '\\html\\Index.html';
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		//alert(xmlHttpReq.responseText);
		TutorialSelector.innerHTML = xmlHttpReq.responseText;
	} catch (error) {
		alert('Error occured while attempting to retreive index:\n'
			+ '(' + Path + ')\n'
			+ error.message + '\n');
	}
}

function LoadLangs() {
	LangSelector.innerHTML = LoadSomeXMLFile(
		'..\\Lang\\Index.xml', 'code', 'ChangeLang');
}

function LoadThemes() {
	ThemeSelector.innerHTML = LoadSomeXMLFile(
		'..\\Themes\\Index.xml', 'name', 'ChangeTheme');
}

function LoadTuts() {
	TutSelector.innerHTML = LoadSomeXMLFile(
		'..\\Lang\\' + Lang + '\\Index.xml', 'name', 'ChangeTut');
}

function LoadSomeXMLFile(Path, PropertyToPass, Method) {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		var XMLText = xmlHttpReq.responseText.split('\n');
		var XMLCode = '';
		var XMLName = '';
		var EndHTML = '';
		for (i = 0; i < XMLText.length; i++) {
			XMLCode = XMLText[i].substring(
				XMLText[i].indexOf('>')+1,
				XMLText[i].lastIndexOf('<'));
			var NameIndex = XMLText[i].indexOf(PropertyToPass + '=') 
			+ PropertyToPass.length + 1;
			XMLName = XMLText[i].substring(
				NameIndex,
				XMLText[i].substring(
					NameIndex)
					.indexOf('"')+NameIndex);
			EndHTML += '<a href="#" onclick="';
			EndHTML += Method;
			EndHTML += '(\'';
			EndHTML += XMLName;
			EndHTML += '\')">';
			EndHTML += XMLCode;
			EndHTML += '</a><br />';
		}
		return EndHTML;
	} catch (error) {
		alert('Error occured while attempting to retreive XML file:\n'
			+ '(' + Path + ')\n'
			+ error.message + '\n');
	}
}

function LoadTheme() {
	//document.getElementsByTagName('body')[0]
	//	.style.behavior = 'url(\'..\\css\\WH3.htc\')'
	//var Stuff = '';
	var CSS = document.getElementsByTagName('link');
	CSS[0].href = '..\\Themes\\' + Them + '\\css\\MainPage.css';
	document.getElementsByTagName('body')[0]
		.style.behavior = 'url(\'..\\css\\WH3.htc\')'
	//Stuff += CSS[0].href;
	//Stuff += '\n';
	var Images = ControlDiv.getElementsByTagName('input');
	for (i = 0; i < Images.length; i++) {
		if (Images[i].src != null) {
			var FileName = Images[i].src.substring(
				Images[i].src.lastIndexOf('/')+1);
			Images[i].src = '..\\Themes\\' + Them + '\\img\\' + FileName;
		}
		//Stuff += Images[i].src;
		//Stuff += '\n';
	}
	//alert(Stuff);
}

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
			NextButton.src = '..\\Themes\\' + Them + '\\img\\Finish.png';
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
		NextButton.src = '..\\Themes\\' + Them + '\\img\\Next.png';
	}
}

function FirstPage() {
	//ToggleTutorialSelector()
	PageNumber=1;
	GotoTutorialPage();
	if (PageNumber < MaxPages) {
		CancelButton.style.display = "inline";
		NextButton.src = '..\\Themes\\' + Them + '\\img\\Next.png';
	}
}

function Page(number) {
	PageNumber = number;
	GotoTutorialPage();
}

function GotoTutorialPage() {
	GotoPage("..\\Lang\\" + Lang + '\\' + CurTut + "\\html\\Page" + PageNumber + ".html");
}

function GotoPage(Path) {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		//alert(xmlHttpReq.responseText);
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
		Images[i].src = Path + 'Lang/'
			+ Lang + '\\' + CurTut + '/img/' + FileName;
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

function ChangeTut(TutorialName) {
	CurTut = TutorialName;
	GotoTutorialPage();
}

function ChangeLang(LanguageCode) {
	Lang = LanguageCode;
	/*BegginingButton.src = "..\\img\\Beggining.png";
	BackButton.src = "..\\img\\Back.png";
	NextButton.src = "..\\img\\Next.png";
	CancelButton.src = "..\\img\\Cancel.png";*/
	GotoTutorialPage();
}

function ChangeTheme(ThemeName) {
	Them = ThemeName;
	LoadTheme();
}

function ToggleTutorialSelectorFunc() {
	//Toggler = TutorialSelectorDiv.style.display;
	TutorialSelector.style.display = 
		(TutorialSelector.style.display == "none")
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
	CodeLinePattern = new RegExp('/<div(\\s+)class="(\\s*)code(\\s*)"(.*?)>/i');
	EndCodeBlock = new RegExp('/<\/div>/i');
	TitleMatch = new RegExp('<title>(.*?)</title>');
	InCodeDiv = false;
	for (i = 0; i < Lines.length; i++) {
		//alert(Lines[i]);
		if (TitleMatch.test(Lines[i])) {
			document.title = Lines[i].substring(
				Lines[i].indexOf(">")+1,
				Lines[i].lastIndexOf("<"));
		} else {
			EndLines += Lines[i];
			EndLines += '\n';
		}
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