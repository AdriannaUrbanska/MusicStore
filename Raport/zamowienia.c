#include <stdlib.h>
#include <libpq-fe.h>
#include <stdio.h>
 
#include <netinet/in.h>
#include <arpa/inet.h>
 
int main(){
	PGresult *result;
	PGconn *conn;
	const char *connection_str = "host=localhost port=5432 dbname=u7urbanska user=u7urbanska password=7urbanska";
	const char *query = "select * from wszystkie_zamowienia_VAR()";
	conn = PQconnectdb(connection_str);

	if (PQstatus(conn) == CONNECTION_BAD) 
    	fprintf(stderr, "Connection to %s failed, %s", connection_str,PQerrorMessage(conn));
	else 
	{
		printf("Connected OK\n");	 
		
		FILE *fptr;
		fptr = fopen("zamowienia.txt", "w");

		if(fptr == NULL)
		{
			printf("Error!");
			exit(1);
    	}

		result = PQexecParams(conn, query, 0, NULL, NULL, NULL, NULL,1);
	 
	 
		if (PQresultStatus(result) != PGRES_TUPLES_OK)
		{
			fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
		    PQclear(result);
		} 
		else 
		{
			int n = 0, r = 0;
			int nrows   = PQntuples(result);
			int nfields = PQnfields(result);
			for(n = 0; n < nfields; n++)
			{
				if ( n != nfields - 1)
					fprintf(fptr, "%s\t", PQfname(result,n));
				else
					fprintf(fptr, "%s\n", PQfname(result,n));
			}

			for(r = 0; r < nrows; r++) 
			{
		    	for(n = 0; n < nfields; n++)
				{
			   		if (n == nfields-1)
			   		{
				   		fprintf(fptr, "%s",PQgetvalue(result,r,n));


						if(r != nrows-1)
							fprintf(fptr,"\n");
			   		}
			   		else
						fprintf(fptr, " %s\t",PQgetvalue(result,r,n));
				}
		  	}
		}

		fclose(fptr);

		PQfinish(conn);

    	return EXIT_SUCCESS;
 	}
}

