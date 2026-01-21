#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <bits/stdc++.h>
int main()
{	
	std::string bytes = "d8:announce33:http://192.168.1.17:9000/announce10:created by18:qBittorrent v5.1.413:creation datei1768735040e4:infod9:file treed8:test.txtd0:d6:lengthi11e11:pieces root32:Ð⑿:_ù*xÏÃfÁ?±#ë)ÁÊ7ÇñB][BMeee6:lengthi11e12:meta versioni2e4:name8:test.txt12:piece lengthi16384e6:pieces20:çP␃/;Â¨ß␝ôvøï␃Caúe12:piece layersdeee";
	int n =bytes.length();
	
	std::string temp ="";
	std::stack<std::string> s;
	bool open = false, close = true;
	for ( char c: bytes ) 
	{	
		switch (c) 
		{
			case 'd':
				if ( !open )
				{
					open = true;
					close = false;
				}
				break;
			case 'e':
				if (!close )
				{
					open  = false;
					close = true;
				}
				s.push(temp);
				temp = "";
				break;
			default:
				temp += c;
		}
	}
	std::vector<std::string> items;
	while ( !s.empty() ) 
	{
		items.push_back(s.top());
		s.pop();

	}
	std::reverse(items.begin(), items.end());
	for ( std::string item : items )
		std::cout << item << "\n";
	return 0;

}
