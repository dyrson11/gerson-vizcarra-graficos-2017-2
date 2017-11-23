class cube
{
    vector<GLfloat> coordinates;
    vector<GLint> localIndexes;
    void ins(int pos)
    {
        coordinates.push_back(coordinates[pos*3]);
        coordinates.push_back(coordinates[pos*3+1]);
        coordinates.push_back(coordinates[pos*3+2]);
    }
    void insNormal(GLfloat b[3])
    {
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 3; j++)
                normals.push_back(b[j]);
    }
public:
    cube(GLfloat a[3], GLfloat b[3], bool incl)
    {
        for ( int q = 0; q < 12; q++ )
        {
            int _indx = q % 3;
            coordinates.push_back( a[_indx] );
        }
        //cout<<coordinates[1*3+2] + 0.1<<" \n";
        coordinates[0+2] = coordinates[1*3+2] = a[2] + 0.1;
        coordinates[2*3+2] = coordinates[3*3+2] = a[2] - 0.1;
        localIndexes.push_back(0); localIndexes.push_back(1); localIndexes.push_back(2);
        localIndexes.push_back(2); localIndexes.push_back(1); localIndexes.push_back(3);
        if(incl == false)
        {
            coordinates[0*3+0] = coordinates[2*3+0] = a[0] - 0.1;
            coordinates[1*3+0] = coordinates[3*3+0] = a[0] + 0.1;
            insNormal(new GLfloat[3]{0.0f, 1.0f, 0.0f});
        }
        else
        {
            coordinates[0*3+1] = coordinates[2*3+1] = a[1] - 0.1;
            coordinates[1*3+1] = coordinates[3*3+1] = a[1] + 0.1;
            insNormal(new GLfloat[3]{-1.0f, 0.0f, 0.0f});
        }
        for ( int q = 0; q < 12; q++ )
        {
            int _indx = q % 3;
            coordinates.push_back( b[_indx] );
        }
        coordinates[4*3+2] = coordinates[5*3+2] = b[2] - 0.1;
        coordinates[6*3+2] = coordinates[7*3+2] = b[2] + 0.1;
        localIndexes.push_back(4); localIndexes.push_back(5); localIndexes.push_back(6);
        localIndexes.push_back(6); localIndexes.push_back(5); localIndexes.push_back(7);
        if(incl == false)
        {
            coordinates[4*3+0] = coordinates[6*3+0] = b[0] - 0.1;
            coordinates[5*3+0] = coordinates[7*3+0] = b[0] + 0.1;
            insNormal(new GLfloat[3]{0.0f, -1.0f, 0.0f});
        }
        else
        {
            coordinates[4*3+1] = coordinates[6*3+1] = b[1] - 0.1;
            coordinates[5*3+1] = coordinates[7*3+1] = b[1] + 0.1;
            insNormal(new GLfloat[3]{1.0f, 0.0f, 0.0f});
        }

        ins(0); ins(1); ins(6); ins(7);
        localIndexes.push_back(8); localIndexes.push_back(10); localIndexes.push_back(11);
        localIndexes.push_back(11); localIndexes.push_back(8); localIndexes.push_back(9);
        insNormal(new GLfloat[3]{0.0f, 0.0f, 1.0f});
        ins(2); ins(3); ins(4); ins(5);
        localIndexes.push_back(12); localIndexes.push_back(13); localIndexes.push_back(14);
        localIndexes.push_back(14); localIndexes.push_back(13); localIndexes.push_back(15);
        insNormal(new GLfloat[3]{0.0f, 0.0f, -1.0f});
        ins(0); ins(2); ins(6); ins(4);
        localIndexes.push_back(16); localIndexes.push_back(17); localIndexes.push_back(19);
        localIndexes.push_back(19); localIndexes.push_back(16); localIndexes.push_back(18);
        ins(1); ins(3); ins(7); ins(5);
        localIndexes.push_back(20); localIndexes.push_back(21); localIndexes.push_back(22);
        localIndexes.push_back(22); localIndexes.push_back(21); localIndexes.push_back(23);
        if(incl == 0)
        {
            insNormal(new GLfloat[3]{-1.0f, 0.0f, 0.0f});
            insNormal(new GLfloat[3]{1.0f, 0.0f, 0.0f});
        }
        else
        {
            insNormal(new GLfloat[3]{0.0f, -1.0f, 0.0f});
            insNormal(new GLfloat[3]{0.0f, 1.0f, 0.0f});
        }
        int sz = g_vertex_buffer_data.size() / 3;
        for(int i = 0; i < coordinates.size(); i++)
        {
            g_vertex_buffer_data.push_back(coordinates[i]);
            /*if(i % 3 == 0)
                cout<<endl<<"vertex "<<i/3<<": ";
            cout<<coordinates[i]<<", ";*/
        }
        for(int i = 0; i < localIndexes.size(); i++)
        {
            indices.push_back(localIndexes[i] + sz);
            /*if(i % 3 == 0)
                cout<<endl<<"indices "<<i/3<<": ";
            cout<<localIndexes[i] + sz<<", ";*/
        }
    }
};
