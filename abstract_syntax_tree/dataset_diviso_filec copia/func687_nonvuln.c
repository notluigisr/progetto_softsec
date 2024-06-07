manager_resume_jobs (GSManager *manager)
{
        if (manager->priv->jobs != NULL) {
                g_hash_table_foreach (manager->priv->jobs, (GHFunc) resume_job, manager);
        }
}