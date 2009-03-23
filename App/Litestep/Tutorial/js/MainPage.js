// Global Variables
var PageNumber = 1; //The tutorial page we are on
var MaxPages = 4; //The number of pages in the turorial
var Lang = "Eng"; // The language
var Them = "Default"; //The theme
var CurTut = "LiteStepPortable Introduction"; //The Tutorial name
var CurStatusTimeout;
var FadeTimeout = new Array(100); // Timout for the fade effect
var TutSelBarLeft = 100;
var ContentDivWidth;

// Handlers
//window.onerror=handleErr;
function LoadingCode() {
	//document.getElementsByTagName('body')[0]
	//	.style.behavior = 'url(\'..\\css\\WH3.htc\')'
	Status('Loading First Page...');
	FirstPage();
	Status('Loading Page Index...');
	LoadIndex();
	Status('Loading Installed Languages...');
	LoadLangs();
	Status('Loading Installed Themes...');
	LoadThemes();
	Status('Loading Installed Tutorials...');
	LoadTuts();
	Status('Loading Current Theme...');
	LoadTheme();
	Resize();
	Status(GetStatus() + 'Done!');
	HideStatus();
	ContentDivWidth = document.body.clientWidth-TutSelBarLeft-10;
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
	var XMLProperties = ['code'];
	LangSelector.innerHTML = LoadSomeXMLFile(
		'..\\Lang\\Index.xml', XMLProperties, 'ChangeLang');
	
	//ParseSomeXMLFile('..\\Lang\\Index.xml', RandomProperties);
}

function LoadThemes() {
	var XMLProperties = ['name'];
	ThemeSelector.innerHTML = LoadSomeXMLFile(
		'..\\Themes\\Index.xml', XMLProperties, 'ChangeTheme');
}

function LoadTuts() {
var XMLProperties = ['name', 'pages'];
	TutSelector.innerHTML = LoadSomeXMLFile(
		'..\\Lang\\' + Lang + '\\Index.xml', XMLProperties, 'ChangeTut');
}

function ParseSomeXMLFile(Path, Properties) {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		var XMLText = xmlHttpReq.responseText.split('\n');
		var XMLCode = '';
		var XMLName = '';
		var EndPropertyArray = new Array();
		for (i = 0; i < XMLText.length; i++) {
			EndPropertyArray[i] = new Array(Properties.length + 1);
			XMLCode = XMLText[i].substring(
				XMLText[i].indexOf('>')+1,
				XMLText[i].lastIndexOf('<'));
			EndPropertyArray[i][0] = XMLCode;
			//alert(XMLCode + '\n' + EndPropertyArray);
			var NameIndex = 0;
			for (j = 0; j < Properties.length; j++) {
				NameIndex = XMLText[i].indexOf(Properties[j] + '=') 
				if (NameIndex > 0) {
					NameIndex += Properties[j].length + 2;
					//alert(XMLText[i] + '\n' + Properties[j] + '\n' + NameIndex);
					EndPropertyArray[i][j+1] = XMLText[i].substring(
						NameIndex,
						XMLText[i].substring(
							NameIndex)
							.indexOf('"')+NameIndex);
				}
			}
		}
		// For debugging...
		/*var EndText = '';
		for (i = 0; i < EndPropertyArray.length; i++) {
			EndText += EndPropertyArray[i] + '\n';
			for (j = 0; j < EndPropertyArray[i].length; j++) {
				EndText += '	' + EndPropertyArray[i][j] + '\n';
			}
		}
		alert(EndText);*/
		return EndPropertyArray;
	} catch (error) {
		alert('Error occured while attempting to retreive XML file:\n'
			+ '(' + Path + ')\n'
			+ error.message + '\n');
	}
}

function LoadSomeXMLFile(Path, PropertiesToPass, Method, OtherPropertyToPass) {
	if (OtherPropertyToPass == null) {
		OtherPropertyToPass = 'this';
	}
	var EndHTML = '';
	//var XMLProperty = PropertiesToPass;
	//alert(PropertiesToPass + '\n' + PropertiesToPass.length);
	var XMLProperties = ParseSomeXMLFile(Path, PropertiesToPass);
	for (i = 0; i < XMLProperties.length; i++) {
		EndHTML += '<a href="#" onclick="';
		EndHTML += Method;
		EndHTML += '(\'';
		for (j = 1; j < PropertiesToPass.length+1; j++) {
			EndHTML += XMLProperties[i][j];
			if (!(j == PropertiesToPass.length)) {
				EndHTML += '\',\'';
			}
		}
		EndHTML += '\',';
		EndHTML += OtherPropertyToPass;
		EndHTML += ')">';
		//EndHTML += 
		EndHTML += XMLProperties[i][0];
		EndHTML += '</a><br />';
	}
	//alert(EndHTML);
	return EndHTML;
}

function LoadTheme() {
	//document.getElementsByTagName('body')[0]
	//	.style.behavior = 'url(\'..\\css\\WH3.htc\')'
	//var Stuff = '';
	var CSS = document.getElementsByTagName('link');
	CSS[0].href = '..\\Themes\\' + Them + '\\css\\MainPage.css';
	//document.getElementsByTagName('body')[0]
	//	.style.behavior = 'url(\'..\\css\\WH3.htc\')'
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
	//if (arguments[0] != null) {
		//Node = arguments[0];
		//alert(Node);
		//alert(Node.innerHTML);
		//Node.parentNode.parentNode.firstChild.innerHTML = Them;
	//}
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
	if (arguments.length > 0) {
		PageNumber = arguments[0];
	}
	Status('Loading Page ' + PageNumber + ' of ' + MaxPages + ' in tutorial ' + CurTut + '...');
	if (GotoPage("..\\Lang\\" + Lang + '\\' + CurTut + "\\html\\Page" + PageNumber + ".html") == 'ERROR') {
		Status(GetStatus() + 'Failed.');
	} else {
		Status(GetStatus() + 'Done!');
	}
	HideStatus();
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
		return 'ERROR';
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
		window.setTimeout('ContentDiv.getElementsByTagName(\'img\')['+i+'].naturalWidth = ContentDiv.getElementsByTagName(\'img\')['+i+'].width', 100+(10*i));
		//window.setTimeout(Images[i].naturalHeight = Images[i].height, 200);
		//alert(Images[i]);
	}
	window.setTimeout('ResizeImages();', 300);
}

function ResizeImages() {
	var Images = ContentDiv.getElementsByTagName('img');
	for (i = 0; i < Images.length; i++) {
		//alert(Images[i].src + '\n' + Images[i].width);
		//var h = Images[i].offsetHeight;
		//var w = Images[i].offsetWidth;
		//alert ('The image size of ' + Images[i].src + ' is '+w+'*'+h)
		if (Images[i].width > ContentDivWidth) {
			Images[i].width = ContentDivWidth-15;
		} else if (Images[i].width < Images[i].naturalWidth) {
			Images[i].width = ContentDivWidth-15;
		}
		//Status(Images[i].width + "    " + Images[i].naturalWidth);
	}
}

function ChangeTut(TutorialName, Pages, Node) {
	CurTut = TutorialName;
	PageNumber = 1;
	MaxPages = Pages
	Status('Loading Tutorial: ' + TutorialName + '...');
	GotoTutorialPage();
	if (Node != null) {
		Node.parentNode.parentNode.firstChild.innerHTML = Node.innerHTML;
	}
	//Status(GetStatus() + ' Done!');
	//HideStatus();
}

function ChangeLang(LanguageCode, Node) {
	Lang = LanguageCode;
	GotoTutorialPage();
	if (Node != null) {
		Node.parentNode.parentNode.firstChild.innerHTML = Node.innerHTML;
	}
}

function ChangeTheme(ThemeName, Node) {
	Them = ThemeName;
	Status('Loading Theme: ' + ThemeName + '...');
	LoadTheme();
	if (Node != null) {
		Node.parentNode.parentNode.firstChild.innerHTML = Node.innerHTML;
	}
	Status(GetStatus() + 'Done!');
	HideStatus();
}

function ToggleTutorialSelectorFunc() {
	TutorialSelector.style.display = 
		(TutorialSelector.style.display == "none")
			? ("block") : ("none");
	ContentDiv.style.width =
		(ContentDiv.style.width == "581px")
			? ("481px") : ("581px");
	/*ContentDiv.style.left =
		(ContentDiv.style.left == "10px")
			? ("110px") : ("10px");*/
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
	EndCodeBlock = new RegExp('<\/div>');
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

function Status(newStatus) {
	var StatusBar = document.getElementById('StatusBar');
	StatusBar.innerHTML = newStatus;
	ShowStatus();
	//window.clearTimeout(CurStatusTimeout);
	//CurStatusTimeout = window.setTimeout(
	//	'HideStatus();'
	//	, 2000);
	
}

function HideStatus() {
	var StatusBar = document.getElementById('StatusBar');
	for (i = 0; i < 100; i=i+5) {
		//alert('StatusBar.style.filter = \'alpha(opacity=\'' + i + '\')\';');
		FadeTimeout[i] = window.setTimeout(
			'StatusBar.style.filter = \'alpha(opacity=' + i + ')\';',
			(i-100)*-10);
		//StatusBar.filters.alpha.opacity
	}
	//StatusBar.style.display = 'none';
}

function ShowStatus() {
	for (i = 0; i < FadeTimeout.length; i++) {
		window.clearTimeout(FadeTimeout[i]);
	}
	StatusBar.style.filter = 'alpha(opacity=100)';
	//HideStatus();
}

function GetStatus() {
	return document.getElementById('StatusBar').innerHTML;
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

function Resize() {
	ContentDivWidth = document.body.clientWidth-TutSelBarLeft-10;
	if (ContentDivWidth > 0) {
		ContentDiv.style.width = ContentDivWidth;
	} //else {
		//window.resizeBy(5, 5);
		//document.body.clientWidth = TutSelBarLeft+20;
	//}
	var ContentDivHeight = document.body.clientHeight-25;
	if (ContentDivHeight > 0) {
		ContentDiv.style.height = ContentDivHeight;
		ToggleTutorialSelector.style.height = ContentDivHeight+5;
	}
	ResizeImages();
}

var dragX = 0;

function MoveTutorialSelBar(e) {
	if (ToggleTutorialSelector.style.left == '')
		ToggleTutorialSelector.style.left = TutSelBarLeft + 'px';
	if (e == null) { e = window.event; htype='move';} 
		dragXoffset=e.clientX-parseInt(ToggleTutorialSelector.style.left);
		dragX = e.clientX;
		document.onmousemove=MoveTutorialSelBarMH;
		document.onmouseup=MoveTutorialSelBarCleanup;
		return false;
}

function MoveTutorialSelBarCleanup(e) {
	document.onmousemove=null;
	document.onmouseup=null;
	ContentDivWidth = document.body.clientWidth-TutSelBarLeft-10;
	if (e == null) { e = window.event; } 
	if (dragX == e.clientX) {
		if (ToggleTutorialSelector.style.left == '0px') {
			ToggleTutorialSelector.style.left = TutSelBarLeft + 'px';
			TutorialSelector.style.width = TutSelBarLeft + 'px';
			var ContentDivWidth = document.body.clientWidth-TutSelBarLeft-10;
			ContentDiv.style.width = ContentDivWidth+'px';
			ResizeImages();
		} else {
			//TutSelBarLeft = 0;
			ToggleTutorialSelector.style.left = 0 + 'px';
			TutorialSelector.style.width = '0px';
			var ContentDivWidth = document.body.clientWidth-10;
			ContentDiv.style.width = ContentDivWidth+'px';
			ResizeImages();
		}
	}
}

function MoveTutorialSelBarMH(e) {
	if (e == null) { e = window.event } 
		ContentDivWidth = document.body.clientWidth-TutSelBarLeft-10;
		if (ContentDivWidth > 200 && e.clientX-dragXoffset > 0) {
			ContentDiv.style.width = ContentDivWidth+'px';
			ToggleTutorialSelector.style.left = TutSelBarLeft+'px';
			TutSelBarLeft = e.clientX-dragXoffset;
			TutorialSelector.style.width = e.clientX-dragXoffset+'px';
			ResizeImages();
		} else if (ContentDivWidth <= 200) {
			//alert(document.body.clientWidth-219);
			TutSelBarLeft = document.body.clientWidth-211;
			//MoveTutorialSelBarCleanup(e);
			//throw 'bah';
		}
		return false;
}