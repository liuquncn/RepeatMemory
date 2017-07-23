
#include "CSVProcessor.h"
#include "..\\BasicModule\\error.h"

#pragma warning(disable : 4786)

bool CSVLine::read(istream & file)
{
	clear();
	if (file.eof()) return false;
	if (!file) error("CSVLine::read(): file error.");
	char line[LINELENGTH];
	char * pline=line;
	file.getline(line,LINELENGTH,'\x0d');
	file.get(); // skip '\x0a'
	while (*pline && *pline!='\x0d')
	{
		char field[LINELENGTH];
		char * pfield=field;
		if (*pline=='"')
		{
			pline++; // skip "
			while (*pline && *pline!='\x0d')
			{
				if (*pline=='"')
				{
					if (*(pline+1)=='"') pline++; // "" => "
					else break;
				}
				if (*pline=='\x0a') *pfield++='\x0d'; // 0a => 0d0a
				*pfield++=*pline++;
			}
			if (*pline=='"') pline++; // skip "
			if (*pline==',') pline++; // skip ,
		}
		else
		{
			while (*pline && *pline!='\x0d')
			{
				if (*pline==',') break;
				if (*pline=='\x0a') *pfield++='\x0d'; // 0a => 0d0a
				*pfield++=*pline++;
			}
			if (*pline==',') pline++; // skip ,
		}
		*pfield=0;
		push_back(string(field));
	}
	return true;
}

void CSVLine::write(ostream & file)
{
	char line[LINELENGTH];
	char * pline=line;
	for (iterator iter=begin();iter!=end();iter++)
	{
		char field[LINELENGTH];
		char * pfield=field;
		strcpy(field,(*iter).data());
		while (*pfield && *pfield!='"' && *pfield!=',') pfield++;
		bool quote=(*pfield!=0);
		pfield=field;
		if (quote)
		{
			*pline++='"';
			while (*pfield)
			{
				if (*pfield=='\x0d') pfield++;
				if (*pfield=='"') *pline++='"';
				*pline++=*pfield++;
			}
			*pline++='"';
		}
		else
		{
			while (*pfield)
			{
				if (*pfield=='\x0d') pfield++;
				*pline++=*pfield++;
			}
		}
		*pline++=',';
	}
	if (pline!=line) pline--;
	*pline=0;
	file << line << "\x0d\x0a";
}

void CSVData::read(istream & file)
{
	clear();
	CSVLine cvsline;
	while (cvsline.read(file))
	{
		push_back(cvsline);
		cvsline.clear();
	}
	if (at(size()-1).empty()) pop_back();
}

void CSVData::write(ostream & file)
{
	for (iterator iter=begin();iter!=end();iter++)
	{
		iter->write(file);
		file << flush;
	}
}
