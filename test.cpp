void GetPaths(ifstream& source, Paths64& paths)
{
  while (true)
  {
    string line;
    stringstream::pos_type last_read_line_pos = source.tellg();
    if (getline(source, line) && GetPath(line, paths))
      continue;
    last_read_line_pos -= 1; // workaround for LF vs LFCR (#764)
    source.seekg(last_read_line_pos, ios_base::beg);
    break;//good
  }
}

bool LoadTestNum(ifstream &source, int test_num,
  Paths64 &subj, Paths64 &subj_open, Paths64 &clip,
  int64_t& area, int64_t& count, ClipType &ct, FillRule &fr)
{
  string line;
  area = 0; count = 0;
  if (test_num <= 0) test_num = 1;
  source.seekg(0, ios_base::beg);
  subj.clear(); subj_open.clear(); clip.clear();

  while (getline(source, line))
  {
    if (test_num)
    {
      if (line.find("CAPTION:") != string::npos) --test_num;
      continue;
    }

    if (line.find("CAPTION:") != string::npos) break; // ie don't go beyond current test

    else if (line.find("INTERSECTION") != string::npos)
      ct = ClipType::Intersection;
    else if (line.find("UNION") != string::npos)
      ct = ClipType::Union;
//nice work
